# git 常用命令

---

## 基本配置

1. 打开Git Bash
2. 设置用户信息
    - git config --global user.name  "名称"
    - git config --global user.email  "邮箱名称"
3. 查看配置信息
    - git config --global user.name
    - git config --global user.email

## 初始化本地仓库

- 目标文件夹位置打开git bash
- 输入指令  git init

## 基础操作指令

- git add  将文件提交到暂存区
    (add .可以提交所有文件 )
- git commit 从暂存区提交到本地仓库(.同理)
    (git commit -m  "注释内容")
- git status   查看文件状态
- git log       查看提交记录

参数

- --all    显示显示所有分支
- --pertty=oneline 将提交信息显示为一行
- --graph 以图的形式显示
- --abbrev--commit 优化显示

Git reflog 所有的操作记录

## 版本回退

Git reset --hard commitID

## 分支

工作区每次只能操作一个分支

- 查看分支
    git  branch
- 新建分支
    git branch 分支名
- 切换分支
    git checkout 分支名
- 合并分支
    git merge 分支名(在分支a时 merge 分支b，表示把b'合并到a上)
- 删除分支
    git branch -d 分支名

常见分支命名:

- master(生产)分支
- develop(开发)分支
- feature分支

## 远程操作

- 绑定远程仓库  
    git remote add origin 地址
- 查看仓库
    git  remote
- 同步本地代码到远程仓库  
    git push origin 分支名
- 克隆到本地
    git clone  仓库路径  本地目录
- 从远程仓库中抓取
    git fetch original  分支名
- 需要合并
    从远程仓库中抓取并合并
    git pull original 分支名
