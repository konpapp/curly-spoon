using System;

namespace Exercise5_WorkflowEngine
{
    partial class Program
    {
        static void Main(string[] args)
        {
            var videoWorkflow = new Workflow();
            videoWorkflow.Add(new Upload());
            videoWorkflow.Add(new WebServiceCall());
            videoWorkflow.Add(new SendNotification());
            videoWorkflow.Add(new SetStatus());

            var videoEngine = new WorkflowEngine(videoWorkflow);
            videoEngine.Run();


            var pictureWorkflow = new Workflow();
            pictureWorkflow.Add(new Upload());
            pictureWorkflow.Add(new WebServiceCall());
            pictureWorkflow.Add(new SendNotification());
            pictureWorkflow.Add(new SetStatus());

            var pictureEngine = new WorkflowEngine(videoWorkflow);
            pictureEngine.Run();
        }
    }

public interface IActivity
{
    void Execute();
}
public class Upload : IActivity
{
    public void Execute()
    {
        Console.WriteLine("Element uploaded in cloud storage.");
    }
}
public class WebServiceCall : IActivity
{
    public void Execute()
    {
        Console.WriteLine("Element ready for encoding.");
    }
}
public class SendNotification : IActivity
{
    public void Execute()
    {
        Console.WriteLine("Notification email sent.");
    }
}
public class SetStatus : IActivity
{
    public void Execute()
    {
        Console.WriteLine("Element record status: Processing");
    }
}

public class Workflow
{
    private readonly List<IActivity> _activities;

    public Workflow()
    {
        _activities = new List<IActivity>();
    }

    public void Add(IActivity activity)
    {
        _activities.Add(activity);
    }

    public List<IActivity> Show()
    {
        return _activities;
    }
}

public class WorkflowEngine
{
    private readonly Workflow _workflow;

    public WorkflowEngine(Workflow workflow)
    {
        this._workflow = workflow;
    }

    public void Run()
    {
        foreach (var activity in _workflow.Show())
            activity.Execute();
    }
}

}
