using System;
using System.Collections.Generic;

namespace StackExample
{
    public class Stack
    {
        private readonly List<object> _list;
        public Stack()
        {
            _list = new List<object>();
        }

        public void Push(object obj)
        {
            if (!(obj == null))
                _list.Add((Int32)obj);
            else
                throw new InvalidOperationException();
        }

        public object Pop()
        {
            var toBeReturned = _list[_list.Count - 1];
            _list.RemoveAt(_list.Count - 1);
            return toBeReturned;
        }
        public void Clear()
        {
            _list.Clear();
        }
    }
}
