# include "pch.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Foundation;

class MainWindow : public WindowT<MainWindow>
{
public:
	MainWindow()
	{
	}
};

class App : public ApplicationT<App, IXamlMetadataProvider>
{
public:
	void OnLaunched(LaunchActivatedEventArgs const&)
	{
		Resources().MergedDictionaries().Append(XamlControlsResources());

		window = make<MainWindow>();
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
