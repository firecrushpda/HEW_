﻿#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------


namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class ScrollViewer;
                ref class Image;
            }
        }
    }
}

namespace SDKTemplate
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class Scenario_Document1 : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        void UnloadObject(::Windows::UI::Xaml::DependencyObject^ dependencyObject);
        void DisconnectUnloadedObject(int connectionId);
    
    private:
        bool _contentLoaded;
    
        class Scenario_Document1_obj1_Bindings;
    
        private: ::Windows::UI::Xaml::Controls::ScrollViewer^ TextLayoutFrame;
        private: ::Windows::UI::Xaml::Controls::Image^ TextLayoutImage;
    };
}

