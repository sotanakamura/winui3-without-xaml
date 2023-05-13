# include "pch.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Foundation;

class MainWindow : public Window
{
public:
	MainWindow()
	{
		StackPanel stackPanel;
		stackPanel.HorizontalAlignment(HorizontalAlignment::Center);
		stackPanel.VerticalAlignment(VerticalAlignment::Center);

		TextBlock title;
		title.Style(Application::Current().Resources().Lookup(box_value(L"TitleTextBlockStyle")).as<Style>());
		title.Text(L"WinUI 3 in C++ Without XAML!");
		title.HorizontalAlignment(HorizontalAlignment::Center);

		HyperlinkButton project;
		project.Content(box_value(L"Github Project Repository"));
		project.NavigateUri(Uri(L"https://github.com/sotanakamura/winui3-without-xaml"));
		project.HorizontalAlignment(HorizontalAlignment::Center);

		Button button;
		button.Content(box_value(L"Click"));
		button.Click([&](IInspectable const& sender, RoutedEventArgs) { sender.as<Button>().Content(box_value(L"Thank You!")); });
		button.HorizontalAlignment(HorizontalAlignment::Center);
		button.Margin(ThicknessHelper::FromUniformLength(20));

		Content(stackPanel);
		stackPanel.Children().Append(title);
		stackPanel.Children().Append(project);
		stackPanel.Children().Append(button);
	}
};

class WinUIApplication
{
	struct XamlApplication : public ApplicationT<XamlApplication, IXamlMetadataProvider>
	{
		void OnLaunched(LaunchActivatedEventArgs const&)
		{
			Resources().MergedDictionaries().Append(XamlControlsResources());
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
		XamlControlsXamlMetaDataProvider provider;
	};
	Application app{ nullptr };
public:
	WinUIApplication()
	{
		app = make<XamlApplication>();
	}
};

int main()
{
	init_apartment();
	Application::Start([](auto) {
		WinUIApplication app;
		Window window;
		window.SystemBackdrop(MicaBackdrop());
		window.Activate();
	});
	return 0;
}
