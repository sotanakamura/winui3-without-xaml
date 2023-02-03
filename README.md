# WinUI 3 in C++ Without XAML
WinUI 3 is a modern UI framework for Windows apps. WinUI 3 can be used with C++/WinRT, a C++17 language projection that provides access to the Windows Runtime (WinRT) APIs. Usually, XAML is used to define the UI. Therefore, XAML and C++ are combined to create applications. However, there are those who want to create simple applications in C++ without XAML. This repository provides a step-by-step guide to creating WinUI3 apps in C++ without XAML.

## Caution
Creating WinUI 3 apps without XAML is an unsupported scenario; it is strongly recommended to use XAML when creating Winui 3 apps. If you still want to create a winui 3 app without XAML, proceed to the next section.

## Step 1: Creating a Project
Normally, when creating a WinUI 3 application, start with a WinUI 3 project template. Here, we start with an empty project.

1. Create an empty project.
2. Set project properties for unpackage WinUI 3 app
    1. Open `.vcxproj` file in any text editor. Or, right-click the project on Solution Explorer of Visual Studio and click "Unload Project".
    2. Add the following properties inside the PropertyGroup element.

        ```xml
          <PropertyGroup Label="Globals">
            <WindowsAppSDKSelfContained>true</WindowsAppSDKSelfContained>
            <WindowsPackageType>None</WindowsPackageType>
            <AppxPackage>false</AppxPackage>
            ...
          </PropertyGroup>
        ```
    
    If you have unloaded the project, right-click on the project and click "Reload Project". Usually, WinUI 3 projects are packaged with MSIX. If you do not want to package it, set the `WindowsPackageType` option and the `AppxPackage` option. In addition, if you want to run the app without installing the Windows App SDK, set the `WindowsAppSDKSelfContained` option to make the app self-contained, including dependencies.
3. Install the Microsoft.Windows.CppWinRT NuGet package to enable support for C++/WinRT and Microsoft.WindowsAppSDK for WinUI 3.
    1. Right-click your project in Solution Explorer and choose Manage NuGet Packages.
    2. Select the Browse tab, search for the Microsoft.Windows.CppWinRT and Microsoft.WindowsAppSDK package, and install the latest version of these packages.
4. Set `/SUBSYSTEM` liker option for the GUI application. 
    1. Right-click on the project and click "Properties".
    2. Set `Windows` in "Linker->System->SubSystem".

## Step 2: Implementing an Entry Point
When the Windows operating system (OS) runs an app, the OS begins execution in the app's entry point. That entry point takes the form of `wWinMain` function instead of `main`. `wWinMain` function is declared in `Windows.h`. Include `Windows.h` and define `wWinMain` function in your code.

```cpp
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	return 0;
}
```

## Step 3: Including C++/WinRT Header Files
C++/WinRT header files for access to Windows SDK APIs and Windows App SDK APIs are generated in your project folder. Include some required header files.

```cpp
#include <Windows.h>
#undef GetCurrentTime
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
```

`#undef GetCurrentTime` is needed to avoid compile error on duplicated macros. `Microsoft.UI.Xaml.h` header file provides general XAML APIs including `Application` class and `Window` class. APIs provided by `Microsoft.UI.Xaml.h` has `winrt::Microsoft::UI::Xaml` namespace. In general, Windows Runtime APIs have `winrt` namespace, Windows SDK APIs have `Windows` namespace, and Windows APP SDk APIs have `Microsoft` namespace. `using namespace` is useful for simplifying code.

## Step 4: Creating an Application and a Window
`Application` class provides an entry point for the WinUI 3 application. `OnLaunched` method is invoked when the application is launched. Inherit `Application` class and override this method to perform application initialization and to create a new window.

```cpp
class App : public ApplicationT<App>
{
public:
	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		window = Window();
		window.Activate();
	}
private:
	Window window = nullptr;
};
```

This inheritance pattern is called F-bound Polymorphism pattern or Curiously Recurring Template Pattern. In `OnLaunched` method, create a new windows and activate it.

## Step 5: Initializing and Start an application
`init_apartment` initializes the thread in the Windows Runtime. ``

## Step 6: Building and Running a WinUI 3 app
