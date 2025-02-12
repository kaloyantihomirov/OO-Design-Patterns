namespace _03.checksum.FileSystem.Observers;

public class ProgressReporter : IObserver
{
    public void Update(string currentFileName)
    {
        Console.WriteLine($"Processing {currentFileName}...");
    }
}