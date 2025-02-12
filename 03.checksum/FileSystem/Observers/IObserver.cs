namespace _03.checksum.FileSystem.Observers;

public interface IObserver
{
    public void Update(ISubject sender, object message);
}

