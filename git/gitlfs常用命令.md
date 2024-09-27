# gitlfs 常用命令

## gitlfs是什么

简单来说，gitlfs（Large File Storage）用来存储内存占用较大的二进制文件
Git LFS 通过将仓库中的大文件替换为微小的指针（pointer） 文件来做到这一点。

## gitlfs使用

1. 安装gitlfs
    下载gitlfs，网址：<https://git-lfs.com/>
2. 在你的git仓库中初始化
    >$ git lfs install
    >Git LFS initialized.
3. 创建新的GitLFS仓库

    > \# initialize Git
    > \$ mkdir Atlasteroids
    > \$ cd Atlasteroids
    > \$ git init
    > Initialized empty Git repository in /Users/tpettersen/Atlasteroids/.git/
    > \# initialize Git LFS

## gitlfs指令

1. gitlfs指令

    > $ git lfs install
    > Updated pre-push hook.
    > Git LFS initialized.
    > git init #创建本地仓库环境
    > git lfs install #安装大文件上传应用
    > git lfs track *#追踪要上传的大文件，*表示路径下的所有文件
    > git add .gitattributes #添加先上传的属性文件(要先上传属性文件，不然有可能失败)
    > git commit -m "pre" #添加属性文件上传的说明
    > git remote add origin <https://github.com/XXXXXXXXXXXXXXXXXXXXXX/XXXXXXXXXXXXXXXXXX.git> #建立本地和Github仓库的链接
    > git push origin master #上传属性文件
    > git add *#添加要上传的大文件，*表示路径下的所有文件
    > git commit -m "Git LFS commit" #添加大文件上传的说明
    > git push origin master #上传大文件
