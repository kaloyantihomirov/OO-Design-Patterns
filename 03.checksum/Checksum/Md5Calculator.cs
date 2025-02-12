using System.Security.Cryptography;
using _03.checksum.FileSystem.Observers;

namespace _03.checksum.Checksum;

public class Md5Calculator : IChecksumCalculator, ISubject
{
    private readonly List<IObserver> observers = new();

    public string Calculate(Stream inputStream)
    {
        using var md5 = MD5.Create();

        byte[] buffer = new byte[4096];
        int bytesRead;
        long totalBytesSoFar = 0;

        while ((bytesRead = inputStream.Read(buffer, 0, buffer.Length)) > 0)
        {
            md5.TransformBlock(buffer, 0, bytesRead, buffer, 0);
            totalBytesSoFar += bytesRead;

            NotifyObservers(totalBytesSoFar);
        }

        md5.TransformFinalBlock([], 0, 0);

        return BitConverter.ToString(md5.Hash).Replace("-", "").ToLowerInvariant();
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