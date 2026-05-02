#include "pch.h"
#include "MainWindow.xaml.h"
#include "MainWindow.g.cpp"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Storage;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Zoller_to_Sinumerik_GROB::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    void MainWindow::transButtonClick(IInspectable const&, RoutedEventArgs const&) {
        std::wstring ws(InputBox().Text().c_str());

        std::wstring token;
        int floatCount = 0;

        //double length = 0.0;
        //double radius = 0.0;

        for (wchar_t c : ws)
        {
            if (c == L';')
            {
                if (!token.empty())
                {
                    // try converting
                    try
                    {
                        double num = std::stod(token);

                        // skip the first number, take next two
                        if (floatCount == 1)
                            length = num;
                        else if (floatCount == 2)
                            radius = num;

                        floatCount++;
                    }
                    catch (...)
                    {
                        // ignore invalid token
                    }

                    token.clear();
                }
            }
            else
            {
                token += c;
            }
        }

        // handle last token (if needed)
        if (!token.empty())
        {
            try
            {
                double num = std::stod(token);

                if (floatCount == 1)
                    length = num;
                else if (floatCount == 2)
                    radius = num;
            }
            catch (...) {}
        }

        // show result
        std::wstring output =
            L"Length from zoller in mm: " + std::to_wstring(length) +
            L"\nRadius from zoller in mm: " + std::to_wstring(radius);

        OutputText().Text(output);

		conv_length = length / 25.4; // convert mm to inches
		conv_radius = radius / 25.4; // convert mm to inches

        std::wstring conv_output =
            L"Length for GROB in inches: " + std::to_wstring(conv_length) +
			L"\nRadius for GROB in inches: " + std::to_wstring(conv_radius);
		ConvertedText().Text(conv_output);
    }
    

    fire_and_forget MainWindow::writeButtonClick(IInspectable const&, RoutedEventArgs const&) {
        StorageFolder folder = ApplicationData::Current().LocalFolder();

        StorageFile file = co_await folder.CreateFileAsync(
            L"GROB_TD.txt",
            CreationCollisionOption::ReplaceExisting
        );

        std::wstring content =
            L"" + std::to_wstring(conv_length) +
            L"\n" + std::to_wstring(conv_radius);

        co_await FileIO::WriteTextAsync(file, content);

        OutputText().Text(L"Saved to GROB_TD.txt");
    }
}
