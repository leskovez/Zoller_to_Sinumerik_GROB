#pragma once

#include "MainWindow.g.h"
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>

namespace winrt::Zoller_to_Sinumerik_GROB::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void transButtonClick(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        winrt::fire_and_forget writeButtonClick(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        double length = 0.0;
        double radius = 0.0;
        double conv_length = 0.0;
        double conv_radius = 0.0;
    };
}

namespace winrt::Zoller_to_Sinumerik_GROB::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
