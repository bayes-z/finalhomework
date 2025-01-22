---
title: 文件管理系统
date: 2025-01-19 19:12:19
tags:

---

------

# 文件管理系统项目实践与总结

在本次项目中，我们设计并实现了一个基于 C 语言和 Linux 命令行工具的文件管理系统。该项目的目标是通过命令行输入实现文件的复制、删除、压缩和解压功能。通过这个项目，我们不仅提升了对 C 语言编程的理解，还深入学习了 Linux 系统调用和命令行工具的使用。

## 项目背景与目标

在日常的文件管理中，我们常常需要对文件进行复制、删除、压缩和解压等操作。虽然这些功能可以通过图形界面工具轻松完成，但在 Linux 系统下，命令行工具提供了更高效、更灵活的解决方案。因此，我们决定开发一个基于命令行的文件管理系统，通过 C 语言调用 Linux 命令行工具（如 `cp`、`rm`、`tar`）来实现这些功能。

项目的主要目标包括：

1. 实现文件复制、删除、压缩和解压功能。
2. 提供用户友好的命令行交互界面。
3. 处理常见的错误情况，并给出清晰的提示信息。
4. 通过 Git 和 GitHub 进行团队协作，提升开发效率。

## 项目实现

### 功能模块设计

项目分为四个主要功能模块：

1. **文件复制**：通过 `cp` 命令实现文件从一个路径复制到另一个路径。
2. **文件删除**：通过 `rm` 命令删除指定路径的文件。
3. **文件压缩**：通过 `tar` 命令将文件或目录压缩成 `.tar.gz` 格式。
4. **文件解压**：通过 `tar` 命令解压 `.tar.gz` 文件到指定目录。

每个模块都通过 `system()` 函数调用 Linux 命令行工具来完成操作。用户通过输入命令选择对应的操作，并根据提示输入必要的路径信息。

### 代码实现

以下是项目的核心代码实现：

#### 文件复制模块

```c
void func_cp() {
    char filepath1[40] = "NULL";
    char filepath2[40] = "NULL";
    int result;
    printf("请输入文件当前路径：\n");
    scanf("%s", filepath1);
    printf("请输入文件目标路径：\n");
    scanf("%s", filepath2);
    char command[100] = "NULL";
    sprintf(command, "cp %s %s", filepath1, filepath2);
    result = system(command);
    if (result == 0)
        printf("文件已复制\n");
    else
        printf("文件复制失败\n");
}
```

#### 文件删除模块

```c
void func_rm() {
    int result;
    char file_path[40] = "NULL";
    printf("请输入文件路径：\n");
    scanf("%s", file_path);
    char command1[100] = "NULL";
    sprintf(command1, "rm %s", file_path);
    result = system(command1);
    if (result == 0)
        printf("文件已删除\n");
    else
        printf("文件删除失败\n");
}
```

#### 文件压缩模块

```c
void func_tar() {
    int result;
    char command[100] = "NULL";
    char current_filepath[40] = "NULL";
    char target_filepath[40] = "NULL";
    char file_name[40] = "NULL";
    printf("请输入待压缩文件名或目录的归档文件名：\n");
    scanf("%s", file_name);
    printf("请输入待压缩文件或目录的地址：\n");
    scanf("%s", current_filepath);
    printf("请输入文件目标位置：\n");
    scanf("%s", target_filepath);
    if (strcmp(current_filepath, "./") == 0) {
        memset(current_filepath, 0, sizeof(current_filepath));
        strcpy(current_filepath, ".");
    }
    sprintf(command, "tar -czvf %s/%s %s", target_filepath, file_name, current_filepath);
    result = system(command);
    if (result == 0)
        printf("文件已压缩\n");
    else
        printf("文件压缩失败\n");
}
```

#### 文件解压模块

```c
void func_untar() {
    int result;
    char source_filepath[40] = "NULL";
    char target_filepath[40] = "NULL";
    char command[100] = "NULL";
    printf("请输入待解压文件或目录的地址：\n");
    scanf("%s", source_filepath);
    printf("请输入目标目录地址：\n");
    scanf("%s", target_filepath);
    if (strcmp(target_filepath, "./") == 0) {
        sprintf(command, "tar -xzvf %s", source_filepath);
        result = system(command);
    } else {
        sprintf(command, "tar -xzvf %s -C %s", source_filepath, target_filepath);
        result = system(command);
    }
    if (result == 0)
        printf("文件已解压\n");
    else
        printf("文件解压失败\n");
}
```

### 用户交互界面

用户通过输入 `copy`、`delete`、`zip`、`unzip` 或 `exit` 来选择对应的操作。程序会根据输入调用相应的功能模块，并提示用户输入必要的路径信息。

## 遇到的困难与解决方法

### 1.字符串拼接问题

#### 问题

在查找`system（）`函数的用法后发现其函数的变量需要是一个完整的字符串，或是字符串变量或是字符串常量。不存在类似于`printf("cp %s %s"char_1,char_2);`这种用占位符直接拼接的使用方式，所以只能通过将多个字符串拼入一个字符串数组中的方式。

#### 解决方案

使用`sprintf()`函数，将多个字符串拼入command字符串数组中，在调用`system(command)`和命令行进行交互

### 2.路径的使用问题

#### 问题

使用`cd 路径`的控制台命令确实可以改变当前所在路径，但是只在命令执行时有效，命令执行结束又会立刻返回当前程序工作路径，同时如果使用`chdir()`的命令永久改变当前路径会在后续完善项目过程中出现不可预知的问题。故不能使用相对路径。

#### 解决方案

全程使用绝对路径，避免切换路径问题。

## 项目收获

通过本次项目，我们不仅掌握了 C 语言编程和 Linux 命令行工具的使用，还提升了团队协作和问题解决的能力。我们学会了如何通过 `system()` 调用 Linux 命令行工具，如何处理用户输入，以及如何进行错误处理。此外，通过 Git 和 GitHub 的协作，我们对版本控制有了更深入的理解。

## 总结

本次文件管理系统项目是一次非常有意义的实践。我们不仅实现了项目目标，还在过程中学到了很多宝贵的经验。未来，我们计划进一步优化代码，增加更多功能，如支持更多文件格式的压缩和解压，以及提供更友好的用户界面。



