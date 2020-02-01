import random

suits = ('♥', '♦', '♠', '♣')
ranks = ('2', '3', '4', '5', '6', '7', '8', '9', '10', 'Jack', 'Queen', 'King', 'Ace')
values = {'2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, '10':10, 'Jack':10,
         'Queen':10, 'King':10, 'Ace':11}

playing = True

class Card:
    
    def __init__(self, rank, suit):
        self.rank = rank
        self.suit = suit
    
    def __str__(self):
        return f'{self.rank} {self.suit}'

class Deck:
    
    def __init__(self):
        self.deck = []  # start with an empty list
        for suit in suits:
            for rank in ranks:
                self.deck.append(Card(rank,suit))
                
    def __str__(self):
        return f'{self.deck}'

    def shuffle(self):
        random.shuffle(self.deck)
        
    def deal(self):
        dealed_card = self.deck[0]
        self.deck.pop(0) #Take the dealed card out of the deck
        return dealed_card

class Hand:
    
    def __init__(self):
        self.cards = []  # start with an empty list as we did in the Deck class
        self.value = 0   # start with zero value
        self.aces = 0    # add an attribute to keep track of aces
        
    
    def add_card(self,card):
        #print(card)
        self.cards.append(card)
        self.value += values[card.rank]
        return self.cards
    
    def adjust_for_ace(self):
        self.aces += 1
        if self.value > 21:
            self.value += 1

class Chips:
    
    
    def __init__(self):
        self.total = 100  # This can be set to a default value or supplied by a user input
        self.bet = 0
        
    def win_bet(self):
        self.total += self.bet
    
    def lose_bet(self):
        self.total -= self.bet


def take_bet(chips):
    while True:
        try:
            player_bet = int(input("How much would you like to bet?: "))
        except:
            print("Please specify an amount")
            continue
        else:
            if player_bet <= chips:
                print(f"Betting {player_bet} chips")
                return player_bet
            else:
                print('Not enough chips!')

def hit(deck,hand):
    
    hand.add_card(deck.deal())
    
    return deck,hand

def hit_or_stand(deck,hand):
    global playing  # to control an upcoming while loop

    while True:
        x = input("Hit or Stand?: ")
        x = x.upper()
        if x == 'HIT':
            hit(deck,hand)
            return deck,hand
        elif x == 'STAND':
            playing = False
            return playing 
        else:
            print('Whaaat')
            print()
            continue

def show_some(player,dealer):
    print('Dealer has a hidden card and:')
    for i in (dealer.cards[1],dealer.cards[-1]):
        if dealer.cards[1]!=dealer.cards[-1]:
            print(i)
        else:
            print(dealer.cards[1])
            break
        
    print()
    print('You have: ')
    for y in player.cards:
        print(y)
    
    
def show_all(player,dealer):
    
    print('Dealer has: ')
    for z in dealer.cards:
        print(z)
    print()
    print('You have: ')
    for x in player.cards:
        print(x)

def player_busts():
    print("Whooops!!! Over 21! Busted")

def player_wins():
    print("Congratz!!!")

def dealer_busts():
    print("Heey it's your lucky day! Dealer busted")
    
def dealer_wins():
    print("Dealer wins! Sorry not sorryyy!")
    
def push():
    pass

def replayability():
    while True:
        rep = input('Continue?: (y/n)')

rep = False
#MAIN 
while True:
    playing=True
    # Print an opening statement
    if not rep == True:
        print("Welcome to Blackjack")
    
    # Create & shuffle the deck, deal two cards to each player
    
    my_deck = Deck()
    my_deck.shuffle()
    
    player = Hand()
    dealer = Hand()
    
    for i in range(0,2):
        player.add_card(my_deck.deal())
        dealer.add_card(my_deck.deal())
        
    show_some(player,dealer) 
        
    # Set up the Player's chips
    if not rep == True:
        player_chips = Chips()
    print()
    print(f'Starting with {player_chips.total} chips')
    
    # Prompt the Player for their bet
    player_chips.bet = take_bet(player_chips.total)
    
    
    # Show cards (but keep one dealer card hidden)

    
    while playing:  # recall this variable from our hit_or_stand function
        
        # Prompt for Player to Hit or Stand
        
        hit_or_stand(my_deck,player)
           
        # Show cards (but keep one dealer card hidden)
 
        show_some(player,dealer)
    
        # If player's hand exceeds 21, run player_busts() and break out of loop
        
        if player.value > 21:
            
            break
        

    # If Player hasn't busted, play Dealer's hand until Dealer reaches 17
    if player.value <= 21:
        print()
        print("Dealer's turn")
    
        while True:


            if dealer.value <= 17 or dealer.value < player.value:
                dealer.add_card(my_deck.deal())
            else:
                break
        
     # Show all cards
    show_all(player,dealer)
   
       # Run different winning scenarios
    if player.value > 21:
        player_busts()
        player_chips.lose_bet()
    elif dealer.value > 21:
        dealer_busts()
        player_chips.win_bet()
    elif dealer.value >= player.value:
        dealer_wins()
        player_chips.lose_bet()
    else:
        player_wins()
        player_chips.win_bet()
            
        
    
    # Inform Player of their chips total 
    
    print()
    print(f'You got {player_chips.total} chips!')
    
    # Ask to play again
    if player_chips.total <= 0:
        print("heyyy... not enough chips... take a break!")
        break
    elif player_chips.total >= 500:
        print("WINNER!")


    while True:
        try:
            replay = input("Continue? (y/n): ")
            replay = replay.lower()
        except:
            print('Huh?')
        else:
            break
        finally:
            rep = True
    if replay == 'n':
        break
   
