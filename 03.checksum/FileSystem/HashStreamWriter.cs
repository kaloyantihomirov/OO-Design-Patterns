﻿    using _03.checksum.Checksum;
    using _03.checksum.FileSystem.ChecksumFormatter;
    using _03.checksum.FileSystem.Observers;

    namespace _03.checksum.FileSystem;

    /* Когато Md5Calculator-ът прочете X байта, уведомява за това слушателите, 
     * прикачени към него (в частност, HashStreamWriter е слушател на Md5Calculator и бива уведомен за настъпилата промяна)
     * Когато HashStreamWriter обработва нов файл, уведомява слушателите си за
     * името на този файл.
     * HashStreamWriter -> Md5Calculator -> ProgressReporter
     */
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
            NotifyObservers(new AllFilesProcessedMsg());
        }

        public override void ProcessFile(FileEntry file)
        {
            using FileStream fs = new FileStream(
                file.GetPath(),
                FileMode.Open,
                FileAccess.Read);

            NotifyObservers(file.GetPath());

            string hashHex = checksumCalculator.Calculate(fs);

            formatter.WriteItem(writer, new FileMetadata(file.GetPath(), file.GetSizeInBytes(), hashHex, true));

            if (stopped)
            {
                NotifyObservers(new UserHasRequestedPauseAfterCurrFileProcessedMsg(( CreateMemento() )));
            }
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
            /* Тук получаваме съответния брой обработени до момента байтове
            от съответния калкулатор за последно започнатия файл.
            Забележете, че тук отново уведомяваме нашите слушатели, но обаче
            за различна по естество промяна, която не произтича от природата ни 
            на издател (следователно не е следствие от промяна в нашето 
            състояние), а на слушател! (което се отразява и в различния тип на
            message параметъра) - вече сме в процес на обработване
            на конкретен файл и на стъпки съответният калкулатор ни налива
            информация за това докъде е достигнал в обработването на файла.
            Работа на ProgressReporter-а е правилно да събере информацията,
            която му се подава и да я визуализира на потребителя.
            В този метод HashStreamWriter класът ефективно демонстрира природата
            си на слушател, като информацията, която получава, я препраща 
            на неговите слушатели.
            */

            if (sender is PauseManager pm && message is PauseSwitch pauseSwitch)
            {
                if (pauseSwitch.Switch)
                {
                    this.stopped = true;
                    //var hswm = CreateMemento();
                    //NotifyObservers(hswm);
                }
                else
                {
                    this.stopped = false;
                }
            }

            NotifyObservers(message);
        }

        public SharedMemento CreateMemento()
        {
          //  return new HashStreamWriterMemento(this.visitedFiles);

            var memento = new SharedMemento
            {
                VisitedFiles = this.visitedFiles
            };

            return memento;
        }

        public void RestoreFromMemento(SharedMemento memento)
        {
            this.visitedFiles = memento.VisitedFiles;
            this.firstDirectory = true;
        }
    }

    public class UserHasRequestedPauseAfterCurrFileProcessedMsg
    {
        public UserHasRequestedPauseAfterCurrFileProcessedMsg(SharedMemento memento)
        {
            Memento = memento;
        }

        public SharedMemento Memento { get; set; }
    }

    public class AllFilesProcessedMsg
    {
    }
