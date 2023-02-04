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

`#undef GetCurrentTime` is needed to avoid compile error on duplicated macros. `Microsoft.UI.Xaml.h` header file provides general XAML APIs including `Application` class and `Window` class. APIs provided by `Microsoft.UI.Xaml.h` has `winrt::Microsoft::UI::Xaml` namespace. In general, Windows Runtime APIs have `winrt` namespace, Windows SDK APIs have `Windows` namespace, and Windows App SDk APIs have `Microsoft` namespace. `using namespace` is useful for simplifying code.

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
	Window window{ nullptr };
};
```

This inheritance pattern is called F-bound Polymorphism pattern or Curiously Recurring Template Pattern. In `OnLaunched` method, create a new windows and activate it.

## Step 5: Initializing and Start an application
In `wWinMain` function, start application by instantiating `App` derived from `application`.

```cpp
int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment();
	Application::Start([](auto&&) {make<App>(); });
	return 0;
}
```

`init_apartment` initializes the thread in the Windows Runtime. `Application::Start` provides the entry point and requests initialization of the application. 
The lambda expression is passed that make `App` to be invoked in the initialization sequence.

## Step 6: Building and Running a WinUI 3 app
Here is the complete code for the program:

```cpp
#include <Windows.h>
#undef GetCurrentTime
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

class App : public ApplicationT<App>
{
public:
	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		window = Window();
		window.Activate();
	}
private:
	Window window{ nullptr };
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment();
	Application::Start([](auto&&) {make<App>(); });
	return 0;
}
```

Build and run the app. You can see a blank window.

## Step 7: Adding WinUI 3 Controls
Add stack panel and button.

```cpp
...
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
...
using namespace Microsoft::UI::Xaml::Controls;
...

	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		window = Window();

		StackPanel stackPanel;
		stackPanel.HorizontalAlignment(HorizontalAlignment::Center);
		stackPanel.VerticalAlignment(VerticalAlignment::Center);

		Button button;
		button.Content(box_value(L"WinUI 3 Without XAML!"));

		window.Content(stackPanel);
		stackPanel.Children().Append(button);

		window.Activate();
	}

...
```

`StackPanel` arranges child elements into a single line that can be oriented horizontally or vertically. Horizontal alignment and vertical alignment are set by properties (Accessors and Mutators in C++). `Button` represents a templated button control that interprets a Click user interaction. `Content` can be passed an instance of any runtime class. But you can't directly pass to such a function a scalar value (such as a numeric or text value), nor an array. Instead, a scalar or array value needs to be wrapped inside a reference class object. That wrapping process is known as boxing the value. C++/WinRT provides the `winrt::box_value` function, which takes a scalar or array value, and returns the value boxed into a reference class object. After creating conrtols, connect child elements to the parent controls.

## Step 8: Adding WinUI 3 Themes
You can add WinUI 3 controls, but it looks UWP controls. You need to add WinUI 3 themes. WinUI 3 themes are written in XAML, so the `App` requires XAML integration. What you need to do is implementing a `IXamlMetadataProvider` interface. This interface implements XAML type resolution and provides the mapping between types used in XAML markup and the corresponding classes implemented in an application or component. The interface is passed as a template parameter.

```cpp
...
#include <winrt/Windows.UI.Xaml.Interop.h>
...
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>

...
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Interop;

class App : public ApplicationT<App, IXamlMetadataProvider>
{
public:
	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		Resources().MergedDictionaries().Append(XamlControlsResources());
		...
	}
	IXamlType GetXamlType(TypeName const& type)
	{
		return provider.GetXamlType(type);
	}
	IXamlType GetXamlType(hstring const& fullname)
	{
		return provider.GetXamlType(fullname);
	}
	com_array<XmlnsDefinition> GetXmlnsDefinitions()
	{
		return provider.GetXmlnsDefinitions();
	}
private:
	...
	XamlControlsXamlMetaDataProvider provider;
};
```

`IXamlMetadataProvider` interface provides XAML type information with following three methods;

* `GetXamlType(TypeName)`
* `GetXamlType(String)`
* `GetXmlnsDefinitions()`

Implement these methods by passing arguments to `XamlControlsXamlMetaDataProvider` class. `XamlControlsXamlMetaDataProvider` class provides XAML type information for WinUI 3. Finally, add WinUI 3 theme to the applicarion by appending WinUI 3 XAML resource to `Resources` property. `XamlControlsResources()` returns default styles for the controls in WinUI 3. 

## Step 9: Building and Running a WinUI 3 app with Fluent Design
Here is the complete code for the program:

```cpp
#include <Windows.h>
#undef GetCurrentTime
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Interop;

class App : public ApplicationT<App, IXamlMetadataProvider>
{
public:
	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		Resources().MergedDictionaries().Append(XamlControlsResources());

		window = Window();

		StackPanel stackPanel;
		stackPanel.HorizontalAlignment(HorizontalAlignment::Center);
		stackPanel.VerticalAlignment(VerticalAlignment::Center);

		Button button;
		button.Content(box_value(L"WinUI 3 Without XAML!"));

		window.Content(stackPanel);
		stackPanel.Children().Append(button);

		window.Activate();
	}
	IXamlType GetXamlType(TypeName const& type)
	{
		return provider.GetXamlType(type);
	}
	IXamlType GetXamlType(hstring const& fullname)
	{
		return provider.GetXamlType(fullname);
	}
	com_array<XmlnsDefinition> GetXmlnsDefinitions()
	{
		return provider.GetXmlnsDefinitions();
	}
private:
	Window window{ nullptr };
	XamlControlsXamlMetaDataProvider provider;
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment();
	Application::Start([](auto&&) {make<App>(); });
	return 0;
}
```

Build and run the app. You can see a beautiful WinUI 3 button.

## Reference
This method is an unsupported scenario; it is strongly recommended to use XAML when creating Winui 3 apps. Please refer to the official documents to get started with [Windows App SDK](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/). If you are not familiar with [C++/WinRT](https://learn.microsoft.com/ja-jp/windows/uwp/cpp-and-winrt-apis/) and [XAML](https://learn.microsoft.com/ja-jp/windows/uwp/xaml-platform/), I highly recommend you to learn them before developing.

* [Windows App SDK](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/): The Windows UI Library (WinUI) 3 is the latest and recommended user interface (UI) framework for Windows desktop apps. By incorporating the Fluent Design System into all experiences, controls, and styles, WinUI provides consistent, intuitive, and accessible experiences using the latest UI patterns. WinUI 3 is available as part of the Windows App SDK.
* [C++/WinRT](https://learn.microsoft.com/ja-jp/windows/uwp/cpp-and-winrt-apis/): C++/WinRT is an entirely standard modern C++17 language projection for Windows Runtime (WinRT) APIs, implemented as a header-file-based library, and designed to provide you with first-class access to the modern Windows API. 
* [XAML](https://learn.microsoft.com/ja-jp/windows/uwp/xaml-platform/): Extensible Application Markup Language (XAML) is a declarative language. Specifically, XAML can initialize objects and set properties of objects using a language structure that shows hierarchical relationships between multiple objects and a backing type convention that supports extension of types. You can create visible UI elements in the declarative XAML markup.

Some text in this document is cited from Microsoft documentation. https://learn.microsoft.com
