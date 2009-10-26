' From http://www.computerhope.com/forum/index.php?topic=93236.0

Set objWord = CreateObject("Word.Application")
strDocPath = "c:\test\test.doc"
strSearch = "word"
Set objDoc = objWord.Documents.Open(strDocPath)
With objDoc.Content.Find
   .Text = strSearch
   .Format = False
   .Wrap = wdFindStop
   Do While .Execute
      iStrCount = iStrCount + 1
   Loop
End With
If iStrCount = 1 Then
  WScript.Echo strSearch & " appears once in" & vbCrLf & strDocPath
Else
  WScript.Echo strSearch & " appears " & iStrCount & " times in " & vbCrLf & strDocPath
End If
objDoc.Close(wdDoNotSaveChanges)
objWord.Quit
Set objWord = Nothing
Set fso = Nothing
