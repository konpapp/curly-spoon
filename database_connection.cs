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

        }

        public override void Close()
        {

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

        }

        public override void Close()
        {

        }

    }
}
