using _03.checksum.FileSystem;
using Xunit;

namespace _03.checksum.Tests;

internal class ExpectedEntry
{
    public string Name { get; set; }
    public bool IsDirectory { get; set; }
    public List<ExpectedEntry> Children { get; set; } = new List<ExpectedEntry>();
}

internal static class DirectoryStructureAssertions
{
    public static void AssertDirectoryMatchesExpected(DirectoryEntry actual, ExpectedEntry expected)
    {
        Assert.Equal(expected.Name, Path.GetFileName(actual.GetPath()));

        var actualChildren = actual.Children.ToList();

        Assert.Equal(expected.Children.Count, actualChildren.Count);

        foreach (var exp in expected.Children)
        {
            if (exp.IsDirectory)
            {
                var matchingDir = actualChildren
                    .OfType<DirectoryEntry>()
                    .FirstOrDefault(d => Path.GetFileName(d.GetPath()) == exp.Name);
                Assert.NotNull(matchingDir);
                AssertDirectoryMatchesExpected(matchingDir, exp);
            }
            else
            {
                var matchingFile = actualChildren
                    .OfType<FileEntry>()
                    .FirstOrDefault(f => Path.GetFileName(f.GetPath()) == exp.Name);
                Assert.NotNull(matchingFile);
            }
        }
    }
}

public class DirectoryBuilderNoSymLinkTests
{
    [Fact]
    public void BuildDirectoryEntry_SimpleFolder_ReturnsCorrectStructure()
    {
        string resourcesPath = Path.Combine(AppContext.BaseDirectory, "Resource", "simpleWithFewTxtFiles");

        var root = DirectoryEntryHelper.BuildRootDirectoryEntryInMem(resourcesPath, false);

        Assert.NotNull(root);
        Assert.Equal(resourcesPath, root.GetPath());

        var children = root.Children.ToList();
        Assert.Equal(3, children.Count);

        var childPaths = children.Select(c => c.GetPath()).ToList();


        Assert.Contains(Path.Combine(resourcesPath, "1.txt"), childPaths);
        Assert.Contains(Path.Combine(resourcesPath, "2.txt"), childPaths);
        Assert.Contains(Path.Combine(resourcesPath, "3.txt"), childPaths);

        Assert.All(children, c => Assert.True(c.GetSizeInBytes() > 0));
    }

    [Fact]
    public void BuildDirectoryEntry_FolderWithSubdirectories_ReturnsCorrectStructure()
    {
        string resourcesPath = Path.Combine(AppContext.BaseDirectory, "Resource", "folderWithSubdirs");

        DirectoryEntry actualRoot = DirectoryEntryHelper.BuildRootDirectoryEntryInMem(resourcesPath, followSymLinks: false);

        var expected = new ExpectedEntry
        {
            Name = "folderWithSubdirs",
            IsDirectory = true,
            Children = new System.Collections.Generic.List<ExpectedEntry>
            {
                new ExpectedEntry { Name = "topLevelFile.txt", IsDirectory = false },
                new ExpectedEntry
                {
                    Name = "subA",
                    IsDirectory = true,
                    Children = new System.Collections.Generic.List<ExpectedEntry>
                    {
                        new ExpectedEntry { Name = "fileA1.txt", IsDirectory = false },
                        new ExpectedEntry { Name = "fileA2.txt", IsDirectory = false }
                    }
                },
                new ExpectedEntry
                {
                    Name = "subB",
                    IsDirectory = true,
                    Children = new System.Collections.Generic.List<ExpectedEntry>
                    {
                        new ExpectedEntry { Name = "fileB1.txt", IsDirectory = false }
                    }
                }
            }
        };

        DirectoryStructureAssertions.AssertDirectoryMatchesExpected(actualRoot, expected);
    }

    [Fact]
    public void BuildDirectoryEntry_ComplexStructure_ReturnsCorrectStructure()
    {
        string resourcesPath = Path.Combine(AppContext.BaseDirectory, "Resource", "complexFolderWithSubdirs");

        DirectoryEntry actualRoot = DirectoryEntryHelper.BuildRootDirectoryEntryInMem(resourcesPath, followSymLinks: false);

        var expected = new ExpectedEntry
        {
            Name = "complexFolderWithSubdirs",
            IsDirectory = true,
            Children = new List<ExpectedEntry>
                {
                    new ExpectedEntry { Name = "topLevelFile.txt", IsDirectory = false },
                    new ExpectedEntry
                    {
                        Name = "subDir1",
                        IsDirectory = true,
                        Children = new List<ExpectedEntry>
                        {
                            new ExpectedEntry { Name = "subFile1.txt", IsDirectory = false },
                            new ExpectedEntry { Name = "subFile2.txt", IsDirectory = false },
                            new ExpectedEntry
                            {
                                Name = "nestedDir",
                                IsDirectory = true,
                                Children = new List<ExpectedEntry>
                                {
                                    new ExpectedEntry { Name = "nestedFile1.txt", IsDirectory = false }
                                }
                            }
                        }
                    },
                    new ExpectedEntry
                    {
                        Name = "subDir2",
                        IsDirectory = true,
                        Children = new List<ExpectedEntry>
                        {
                            new ExpectedEntry { Name = "subFileA.txt", IsDirectory = false },
                            new ExpectedEntry { Name = "subFileB.txt", IsDirectory = false }
                        }
                    }
                }
        };

        DirectoryStructureAssertions.AssertDirectoryMatchesExpected(actualRoot, expected);
    }

    [Fact]
    public void BuildDirectoryEntry_StructureVeryNestedDirs_ReturnsCorrectStructure()
    {
        string resourcesPath = Path.Combine(AppContext.BaseDirectory, "Resource", "nestedDirs");

        DirectoryEntry actualRoot = DirectoryEntryHelper.BuildRootDirectoryEntryInMem(resourcesPath, followSymLinks: false);

        var expected = new ExpectedEntry
        {
            Name = "nestedDirs",
            IsDirectory = true,
            Children = new List<ExpectedEntry>
            {
                new ExpectedEntry
                {
                    Name = "n1",
                    IsDirectory = true,
                    Children = new List<ExpectedEntry>
                    {
                        new ExpectedEntry
                        {
                            Name = "n2",
                            IsDirectory = true,
                            Children = new List<ExpectedEntry>
                            {
                                new ExpectedEntry
                                {
                                    Name = "n3",
                                    IsDirectory = true,
                                    Children = new List<ExpectedEntry>
                                    {
                                        new ExpectedEntry
                                        {
                                            Name = "n4",
                                            IsDirectory = true,
                                            Children = new List<ExpectedEntry>
                                            {
                                                new ExpectedEntry { Name = "veryNested.txt", IsDirectory = false }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        };

        DirectoryStructureAssertions.AssertDirectoryMatchesExpected(actualRoot, expected);
    }

    [Fact]
    public void BuildDirectoryEntry_DoesNotFollowShortcuts_ReturnsCorrectStructure()
    {
        string resourcesPath = Path.Combine(AppContext.BaseDirectory, "Resource", "dirWithShortcut");

        DirectoryEntry actualRoot = DirectoryEntryHelper.BuildRootDirectoryEntryInMem(resourcesPath, followSymLinks: false);

        var expected = new ExpectedEntry
        {
            Name = "dirWithShortcut",
            IsDirectory = true,
            Children = new List<ExpectedEntry>
            {
                new ExpectedEntry { IsDirectory = false, Name = "shortcut.lnk" },
                new ExpectedEntry { IsDirectory = false, Name = "text.txt" }
            }
        };

        DirectoryStructureAssertions.AssertDirectoryMatchesExpected(actualRoot, expected);
    }
}

public class SymLinkAwareDirectoryBuilder
{
    [Fact]
    public void SymLinkAwareDirectoryBuilder_FollowsSymlinksCorrectly()
    {
        //string resourcesPath = Path.Combine(AppContext.BaseDirectory, "Resource", "dirWithShortcut");

        //DirectoryEntry actualRoot = DirectoryEntryHelper.BuildRootDirectoryEntryInMem(resourcesPath, followSymLinks: true);

        //var expected = new ExpectedEntry
        //{
        //    Name = "dirWithShortcut",
        //    IsDirectory = true,
        //    Children = new List<ExpectedEntry>
        //    {
        //        new ExpectedEntry { IsDirectory = false, Name = "text.txt" },
        //        new ExpectedEntry
        //        {
        //            Name = "subA",
        //            IsDirectory = true,
        //            Children = new System.Collections.Generic.List<ExpectedEntry>
        //            {
        //                new ExpectedEntry { Name = "fileA1.txt", IsDirectory = false },
        //                new ExpectedEntry { Name = "fileA2.txt", IsDirectory = false }
        //            }
        //        },
        //        new ExpectedEntry
        //        {
        //            Name = "subB",
        //            IsDirectory = true,
        //            Children = new System.Collections.Generic.List<ExpectedEntry>
        //            {
        //                new ExpectedEntry { Name = "fileB1.txt", IsDirectory = false }
        //            }
        //        }
        //    }
        //};

        //DirectoryStructureAssertions.AssertDirectoryMatchesExpected(actualRoot, expected);
    }

    [Fact]
    public void SymLinkAwareDirectoryBuilder_HandlesScenarioWithCyclicSymlinks()
    {
    }

    [Fact]
    public void SymLinkAwareDirectoryBuilder_HandlesScenarioWhenShortcutToAlreadyScannedDirectory()
    {

    }

    [Fact]
    public void SymLinkAwareDirectoryBuilder_HandlesScenarioWhenShortcutToAlreadyScannedFile()
    {

    }

    [Fact]
    public void SymLinkAwareDirectoryBuilder_HandlesScenarioWithChainedSymlinksLeadingToUnprocessedEntries()
    {

    }


}