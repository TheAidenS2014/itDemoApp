#pragma once

#include "MainPage.g.h"
#include <vector>
#include <fstream>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.h>
#include <Windows.UI.Xaml.Controls.h>
#include <windows.globalization.h>

namespace itDemoApp
{
	public ref class TicketComment sealed
	{
	public:
		property Platform::String^ From;
		property Platform::String^ Message;
		property Platform::String^ Date;

		TicketComment(Platform::String^ in_from, Platform::String^ in_message, Platform::String^ in_date)
		{
			this->From = in_from;
			this->Message = in_message;
			this->Date = in_date;
		}
	};

	public ref class TicketItem sealed
	{
	private:
		Windows::Foundation::Collections::IVector<TicketComment^>^ contained_comments;

	public:
		property Platform::String^ Sender;
		property Platform::String^ Subject;
		property Platform::String^ Body;
		property Platform::String^ Date;

		property Windows::Foundation::Collections::IVector<TicketComment^>^ OurComments
		{
			Windows::Foundation::Collections::IVector<TicketComment^>^ get()
			{
				return contained_comments;
			}
		}

		TicketItem(Platform::String^ in_sender, Platform::String^ in_subject, Platform::String^ in_date, Platform::String^ in_body)
		{
			this->Sender = in_sender;
			this->Subject = in_subject;
			this->Body = in_body;
			this->Date = in_date;
			contained_comments = ref new Platform::Collections::Vector<TicketComment^>();
		}
	};

	public ref class MainPage sealed
	{
	private:
		Windows::Foundation::Collections::IVector<TicketItem^>^ contained_tickets;
	public:
		MainPage();
		void InboxSidePanel_SelectionChanged(Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void NewTicket_Click(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void NewComment_Click(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		property Windows::Foundation::Collections::IVector<TicketItem^>^ EmailItems
		{
			Windows::Foundation::Collections::IVector<TicketItem^>^ get()
				{
					return contained_tickets;
				}
		}
	};
}
