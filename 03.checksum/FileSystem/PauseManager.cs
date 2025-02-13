using _03.checksum.FileSystem.Observers;

namespace _03.checksum.FileSystem;

public class PauseManager : ISubject
{
    private readonly List<IObserver> observers = new List<IObserver>();

    public bool PauseRequested { get; private set; }

    public void RequestPause()
    {
        this.PauseRequested = true;
        NotifyObservers("PAUSE");
    }

    public void RequestResume()
    {
        this.PauseRequested = false;
        NotifyObservers("RESUME");
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
}