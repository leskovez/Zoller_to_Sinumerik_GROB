#pragma once

#include "App.xaml.g.h"

namespace winrt::Zoller_to_Sinumerik_GROB::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
