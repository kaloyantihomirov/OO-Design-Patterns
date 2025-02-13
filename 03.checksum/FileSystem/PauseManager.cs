using _03.checksum.FileSystem.Observers;

namespace _03.checksum.FileSystem;

public class PauseManager : ISubject, IObserver
{
    private readonly List<IObserver> observers = new List<IObserver>();

    private readonly HashStreamWriter hashStreamWriter;
    private readonly ProgressReporter progressReporter;

    private SharedMemento memento;

    public PauseManager(HashStreamWriter hashStreamWriter, ProgressReporter progressReporter)
    {
        this.hashStreamWriter = hashStreamWriter;
        this.progressReporter = progressReporter;
    }

    public bool PauseRequested { get; private set; }

    public void RequestPause()
    {
        this.PauseRequested = true;
        NotifyObservers(new PauseSwitch(true)); 
       // memento = hashStreamWriter.CreateMemento();
    }

    public void RequestResume()
    {
        this.PauseRequested = false;
        NotifyObservers(new PauseSwitch(false));
        hashStreamWriter.RestoreFromMemento(memento);
        progressReporter.RestoreFromMemento(memento);
    }

    public void RegisterObserver(IObserver observer)
    {
        this.observers.Add(observer);
    }

    public void RemoveObserver(IObserver observer)
    {
        this.observers.Remove(observer);
    }

    public void NotifyObservers(object message)
    {
        foreach (var observer in observers)
        {
            observer.Update(this, message);
        }
    }

    public void Update(ISubject sender, object message)
    {
        if (sender is HashStreamWriter hsw && message is UserHasRequestedPauseAfterCurrFileProcessedMsg m)
        {
            memento = m.Memento;
        }
    }
}

public class PauseSwitch
{
    public PauseSwitch(bool sw)
    {
        this.Switch = sw;
    }

    public bool Switch { get; set; }
}
