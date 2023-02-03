# WinUI 3 in C++ Without XAML
WinUI 3 is a modern UI framework for Windows apps. WinUI 3 can be used with C++/WinRT, a C++17 language projection that provides access to the Windows Runtime (WinRT) APIs. Usually, XAML is used to define the UI. Therefore, XAML and C++ are combined to create applications. However, there are those who want to create simple applications in C++ without XAML. This repository provides a step-by-step guide to creating WinUI3 apps in C++ without XAML.

## Caution
Creating WinUI 3 apps without XAML is an unsupported scenario; it is strongly recommended to use XAML when creating Winui 3 apps. If you still want to create a winui 3 app without XAML, proceed to the next section.

## Step 1: Create a Project
Normally, when creating a WinUI 3 application, start with a WinUI 3 project template. Here, we start with an empty project.

1. Create an empty project.
2. Open `.vcxproj` file in any text editor. Or, right-click the project on Solution Explorer of Visual Studio and click "Unload Project". Add the following properties inside the PropertyGroup element.

    ```xml
      <PropertyGroup Label="Globals">
        <WindowsAppSDKSelfContained>true</WindowsAppSDKSelfContained>
        <WindowsPackageType>None</WindowsPackageType>
        <AppxPackage>false</AppxPackage>
        ...
      </PropertyGroup>
    ```
    
    Usually, WinUI 3 projects are packaged with MSIX. If you do not want to package it, set the WindowsPackageType option and the AppxPackage option. In addition, if you want to run the app without installing the Windows App SDK, set the WindowsAppSDKSelfContained option to make the app self-contained, including dependencies.
3. Install the Microsoft.Windows.CppWinRT NuGet package to enable support for C++/WinRT and Microsoft.WindowsAppSDK for WinUI 3.
    1. Right-click your project in Solution Explorer and choose Manage NuGet Packages.
    2. Select the Browse tab, search for the Microsoft.Windows.CppWinRT and Microsoft.WindowsAppSDK package, and install the latest version of these packages.
