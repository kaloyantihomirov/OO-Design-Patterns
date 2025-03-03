﻿namespace _03.checksum.FileSystem.Observers;

public interface ISubject
{
    public void RegisterObserver(IObserver observer);
    public void RemoveObserver(IObserver observer);
    public void NotifyObservers(object message);
}