import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initializing lists
    overview = []
    row = []
    stockValue = 0
    # Get list of stocks
    stocks = db.execute(f'SELECT DISTINCT stock_symbol FROM transactions WHERE buyer_id={session["user_id"]} GROUP BY stock_symbol')
    for element in stocks:

        stock = lookup(element["stock_symbol"])
        shares = db.execute(f'SELECT SUM(number_of_stocks) FROM transactions WHERE buyer_id={session["user_id"]} AND stock_symbol="{stock["symbol"]}"')

        # Skip if 0 shares left
        if shares[0]["SUM(number_of_stocks)"] == 0:
            continue

        # Add stock symbol
        row.append(stock["symbol"])

        # Add company name
        row.append(stock["name"])

        # Add number of shares
        row.append(shares[0]["SUM(number_of_stocks)"])

        # Add current stock price
        row.append(usd(stock["price"]))

        # Add stock total price
        row.append(usd(shares[0]["SUM(number_of_stocks)"] * stock["price"]))
        stockValue += shares[0]["SUM(number_of_stocks)"] * stock["price"]

        # Add row in overview table
        overview.append(row)
        row = []

    cash = int(db.execute(f'SELECT cash FROM users WHERE id={session["user_id"]}')[0]["cash"])
    total = usd(stockValue + cash)
    balance = usd(cash)

    return render_template("index.html", overview=overview, total=total, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        # Check that symbol exists
        if not lookup(symbol):
            return apology("symbol does not exist")

        shares = int(request.form.get("shares"))
        # Check that the number of bought shares is positive
        if shares <= 0:
            return apology("specify a valid number for shares to buy")

        # Current price of shares
        stockPrice = lookup(symbol)["price"]
        companyName = lookup(symbol)["name"]
        totalPrice = stockPrice * shares

        # Retrieve user cash balance from db and check versus current shares price
        currentID = session["user_id"]
        row = db.execute("SELECT cash FROM users WHERE id=:currentID", currentID=currentID)
        currentCash = row[0]["cash"]
        if totalPrice > currentCash:
            return apology("not enough cash")

        # Create manually new SQL table with commands below, list the purchase in transactions table, update total balance
        # db.execute("CREATE TABLE transactions (transaction_id INT, buyer_id INT, stock_symbol TEXT, number_of_stocks NUMERIC, price NUMERIC, date TEXT, FOREIGN KEY(buyer_id) REFERENCES users(id))")
        # db.execute("CREATE UNIQUE INDEX transaction_index ON transactions (transaction_id)")

        transactions = len(db.execute("SELECT transaction_id FROM transactions")) + 1
        db.execute("INSERT INTO transactions (transaction_id, buyer_id, stock_symbol, number_of_stocks, price, date) VALUES (:transactions, :currentID, :symbol, :shares, :totalPrice, CURRENT_TIMESTAMP)", transactions=transactions, currentID=currentID, symbol=symbol, shares=shares, totalPrice=totalPrice)
        balance = currentCash - totalPrice
        db.execute(f"UPDATE users SET cash={balance} WHERE id={currentID}")

    flash(f'{shares} shares of {companyName} purchased successfully!')
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Initializing lists
    overview = []
    row = []

    # Get list of transactions
    transactions = db.execute(f'SELECT stock_symbol, number_of_stocks, price, date FROM transactions WHERE buyer_id={session["user_id"]} ORDER BY transaction_id DESC')
    for element in transactions:
        # Add stock symbol
        row.append(element["stock_symbol"])

        stock=lookup(element["stock_symbol"])
        # Add company name
        row.append(stock["name"])

        # Add number of shares
        row.append(element["number_of_stocks"])

        # Add price at that time
        row.append(usd((element["price"])))

        # Add datetime of transaction
        row.append(element["date"])

        # Add row in overview table
        overview.append(row)
        row = []

    return render_template("history.html", overview=overview)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol").upper()

        # The commented lines below are implemented in function lookup() in helpers.py
        # apikey = os.environ.get("API_KEY")
        # url = "https://cloud-sse.iexapis.com/stable/stock/" + symbol + "/quote?token=" + apikey

        stock = lookup(symbol)

        stockSymbol = stock["symbol"]
        companyName = stock["name"]
        stockPrice = usd(stock["price"])

        return render_template("quoted.html", stockSymbol=stockSymbol, companyName=companyName, stockPrice=stockPrice)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        if not username:
            return apology("Enter valid username")

        # Check that passwords match
        password0 = request.form.get("password0")
        password1 = request.form.get("password1")
        if password0 != password1:
            return apology("Passwords should match")
        password = password0

        # Check for empty password
        if not password:
            return apology("Enter valid password")

        # Assign new userID
        ids = db.execute("SELECT id FROM users")
        ID = len(ids) + 1

        hashPass = generate_password_hash(password)
        db.execute("INSERT INTO users (id, username, hash) VALUES (:ID, :username, :hashPass)", ID=ID, username=username, hashPass=hashPass)

        flash('Registration successful!')
        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        currentShares = []
        ownedShares = db.execute(f'SELECT DISTINCT stock_symbol FROM transactions WHERE buyer_id={session["user_id"]} GROUP BY stock_symbol')
        for element in ownedShares:
            shares = db.execute(f'SELECT SUM(number_of_stocks) FROM transactions WHERE buyer_id={session["user_id"]} AND stock_symbol="{element["stock_symbol"]}"')
            print(shares)
            # Skip if 0 shares left
            if shares[0]["SUM(number_of_stocks)"] == 0:
                continue

            currentShares.append(element["stock_symbol"])

        return render_template("sell.html", currentShares=currentShares)
    else:
        symbol = request.form.get("symbol")
        # Check that symbol exists
        if not lookup(symbol):
            return apology("symbol does not exist")

        selledShares = int(request.form.get("shares"))
        ownedShares = db.execute(f'SELECT SUM(number_of_stocks) FROM transactions WHERE buyer_id={session["user_id"]} AND stock_symbol="{symbol}"')[0]["SUM(number_of_stocks)"]
        if selledShares < 0 or selledShares > ownedShares:
            return apology("specify valid number of shares to sell")

        # Current price of shares
        stockPrice = lookup(symbol)["price"]
        companyName = lookup(symbol)["name"]
        totalPrice = stockPrice * selledShares

        shares = ownedShares - selledShares

        transactions = len(db.execute("SELECT transaction_id FROM transactions")) + 1
        db.execute("INSERT INTO transactions (transaction_id, buyer_id, stock_symbol, number_of_stocks, price, date) VALUES (:transactions, :currentID, :symbol, :shares, :sellPrice, CURRENT_TIMESTAMP)", transactions=transactions, currentID=session["user_id"], symbol=symbol, shares=-selledShares, sellPrice=totalPrice)

        # Retrieve user cash balance from db and update
        currentCash = db.execute("SELECT cash FROM users WHERE id=:currentID", currentID=session["user_id"])[0]["cash"]

        balance = currentCash + totalPrice
        db.execute(f'UPDATE users SET cash={balance} WHERE id={session["user_id"]}')
    flash(f'{selledShares} shares of {companyName} sold!')
    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

