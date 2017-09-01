---
  **删除git上的文件**

通常只需要以下几个步骤：
```git
git rm -r -n --cached [file]
// -n ，加上这个参数，执行命令时，不会删除任何文件，而是仅展示此命令要删除的文件
```
``` git
git rm -r --cached [file] //执行删除[file]命令
```
```git
git commit -m "00" //提交commit
```
``` git
git push origin master //提交到远程服务器，其实，如果目前远程只有一个remote，也不需要origin master
```
*如果文件的名字中有空格，则需要用转义符来转义*，如：
``` git
git rm -r some\ tips //此处说明删除的文件名为some tips
```
---
