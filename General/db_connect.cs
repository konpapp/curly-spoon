using System;

namespace Exercise4_DatabaseConnection
{
    public abstract class DbConnection
    {
        private readonly string _connectionString;
        private readonly DateTime _connectionStartTime;

        public TimeSpan Timeout
        {
            get
            {
                var connectionTimeSpan = DateTime.Now - _connectionStartTime;
                return connectionTimeSpan;
            }
        }

        public DbConnection(string ConnectionString)
        {
            if (!(String.IsNullOrWhiteSpace(ConnectionString)))
            {
                _connectionString = ConnectionString;
                _connectionStartTime = DateTime.Now;
            }
            else
                throw new ArgumentNullException();
        }

        public abstract void Open();
        public abstract void Close();

    }
        public class DbCommand
    {
        public DbCommand(DbConnection DbConnection)
        {
            if (DbConnection is null)
            {
                throw new ArgumentNullException(nameof(DbConnection));
            }
            else
                this.DbConnection = DbConnection;
        }

        public DbConnection DbConnection { get; }
        public string Instruction { get; set; }


        public void Execute()
        {
            this.DbConnection.Open();
            Console.WriteLine(this.Instruction);
            this.DbConnection.Close();
        }
    }
        public class SqlConnection : DbConnection
    {
        private readonly string _connectionString;

        public SqlConnection(string ConnectionString)
            : base(ConnectionString)
        {
            _connectionString = ConnectionString;
        }

        public override void Open()
        {
            Console.WriteLine("SQL connection opened.");
        }

        public override void Close()
        {
            Console.WriteLine("SQL connection closed.");
        }

    }
        public class OracleConnection : DbConnection
    {
        private readonly string _connectionString;

        public OracleConnection(string ConnectionString)
            : base(ConnectionString)
        {
            _connectionString = ConnectionString;
        }

        public override void Open()
        {
            Console.WriteLine("Oracle connection opened.");
        }

        public override void Close()
        {
            Console.WriteLine("Oracle connection closed.");
        }

    }
        class Program
    {
        static void Main(string[] args)
        {
            var connect = new SqlConnection("421431");
            var newCommand = new DbCommand(connect);
            newCommand.Instruction = "Do this do that";
            newCommand.Execute();
        }
    }
}
