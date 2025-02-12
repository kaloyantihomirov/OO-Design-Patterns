using _03.checksum.Checksum;
using _03.checksum.FileSystem.ChecksumFormatter;
using _03.checksum.FileSystem.Observers;

namespace _03.checksum.FileSystem;

//The progress indicator displays the name of the current file and the number of bytes
// processed so far
public class HashStreamWriter : AbstractVisitor, ISubject, IObserver
{
    private readonly IChecksumCalculator checksumCalculator;
    private readonly StreamWriter writer;
    private readonly IChecksumFormatter formatter;

    private readonly List<IObserver> observers = new();

    public HashStreamWriter(IChecksumCalculator checksumCalculator, 
        StreamWriter writer,
        IChecksumFormatter formatter)
    {
        this.checksumCalculator = checksumCalculator;
        this.writer = writer;
        this.formatter = formatter;

        if (this.checksumCalculator is ISubject calcSubj)
        {
            calcSubj.RegisterObserver(this);
        }
    }

    public override void BeforeDirectoryTraversal()
    {
        formatter.StartReport(writer);
    }

    public override void AfterDirectoryTraversal()
    {
        formatter.EndReport(writer);
    }

    public override void ProcessFile(FileEntry file)
    {
        using FileStream fs = new FileStream(
            file.GetPath(),
            FileMode.Open,
            FileAccess.Read);

        string hashHex = checksumCalculator.Calculate(fs);

        formatter.WriteItem(writer, new FileMetadata(file.GetPath(), file.GetSizeInBytes(), hashHex, true));
        NotifyObservers(file.GetPath());
    }

    public void RegisterObserver(IObserver observer)
    {
        this.observers.Add(observer);
    }

    public void RemoveObserver(IObserver observer)
    {
        this.observers.Remove(observer);
    }

    public void NotifyObservers(object path)
    {
        foreach (var observer in observers)
        {
            observer.Update(this, path);
        }
    }

    public void Update(ISubject sender, object message)
    {
        NotifyObservers(message);
    }
}