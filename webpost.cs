using System;

namespace Exercise2_WebsitePost
{
    public class Post
    {
        public string Title;
        public string Description;
        public DateTime TimeCreated;
        private int _voteStatus = 0;


        public void Upvote()
        {
            _voteStatus += 1;
        }

        public void Downvote()
        {
            _voteStatus -= 1;
        }

        public int Status()
        {
            return _voteStatus;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            var randomPost = new Post();
            Console.WriteLine("Title: ");
            Console.ReadLine();
            Console.WriteLine("Description: ");
            Console.ReadLine();
            randomPost.TimeCreated = DateTime.Now;

            Console.WriteLine("How would you like to react on this post?\n 'like', 'dislike', 'status', 'exit'");
            while (true)
            {
                var input = Console.ReadLine().ToLower();
                if (input == "exit")
                    break;
                else if (input == "like")
                    randomPost.Upvote();
                else if (input == "dislike")
                    randomPost.Downvote();
                else if (input == "status")
                {
                    Console.WriteLine(randomPost.Status());
                    Console.WriteLine("Post created on: " + randomPost.TimeCreated);
                }
                else
                    throw new InvalidOperationException();

            }

        }
    }
}

