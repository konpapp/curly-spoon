using System;
using System.Runtime.Remoting.Metadata.W3cXsd2001;
using System.Security.Cryptography.X509Certificates;

namespace Exercise1_Stopwatch
{
    public class Stopwatch
    {
        public DateTime StartTime;
        public TimeSpan Duration;

        public DateTime Start()
        {
            StartTime = DateTime.Now;
            return StartTime;
        }

        public TimeSpan Stop()

        {
            var stopTime = DateTime.Now;
            var Duration = stopTime - StartTime;
            return Duration;
        }

        public void Reset()
        {
        }
    }
}
