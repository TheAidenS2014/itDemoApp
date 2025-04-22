//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
//#include "MainWorkerFuncs.h"
#include "ReadingDummyTickets.h"

using namespace itDemoApp;

// "using ALL the namespaces!"
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Markup;
using namespace Windows::Globalization;
using namespace Windows::UI::ViewManagement;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

void GrabOptionFromFile(std::ifstream& file, const std::string& endMarker, Windows::UI::Xaml::Controls::ComboBox^ comboBox)
{
    std::string line;
    while (std::getline(file, line))
    {
        if (line == endMarker)
        {
            break;
        }
        
        // convert string to platform string
        auto option = ref new Platform::String(std::wstring(line.begin(), line.end()).c_str());
        comboBox->Items->Append(option);
    }
}

namespace itDemoApp {
    MainPage::MainPage()
    {
        InitializeComponent();
        ApplicationView::GetForCurrentView()->Title = "AidDesk";

        //auto quick_tickets = ref new Platform::Collections::Vector<itDemoApp::TicketItem^>();
        Platform::Collections::Vector<itDemoApp::TicketItem^>^ quick_tickets = ref new Platform::Collections::Vector<itDemoApp::TicketItem^>();

        get_the_dummy_data(quick_tickets);

        // bind the vector
        contained_tickets = quick_tickets;
        InboxSidePanel->ItemsSource = contained_tickets;

        //this->DataContext = this;
    }

    // updates main pane text
    void MainPage::InboxSidePanel_SelectionChanged(Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
    {
        auto selectedItem = dynamic_cast<TicketItem^>(InboxSidePanel->SelectedItem);
        if (selectedItem != nullptr)
        {
            TitleTextBlock->Text = selectedItem->Subject;
            StatusTextBlock->Text = "Status: Open"; // Example status
            ContentTextBlock->Text = "From: " + selectedItem->Sender + "\n\n" + selectedItem->Body;
            CommentsListView->ItemsSource = selectedItem->OurComments;
        }
    }

    void MainPage::NewTicket_Click(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
    {
        std::ifstream grabbedTicketData("Data/tickets_all_options.txt");

        // create pop-up itself
        auto dialog = ref new Windows::UI::Xaml::Controls::ContentDialog();
        dialog->Title = "New Ticket";
        auto panel = ref new StackPanel();

        // ticket title box
        auto titleTextBox = ref new TextBox();
        titleTextBox->Header = "Ticket Title:";
        titleTextBox->PlaceholderText = "Enter the title of the ticket";
        panel->Children->Append(titleTextBox);

        // create dropdown items
        auto comboBox_typeSelector = ref new ComboBox();
        comboBox_typeSelector->Header = "Type:";
        auto comboBox_placeSelector = ref new ComboBox();
        comboBox_placeSelector->Header = "Place:";
        auto roomNumberTextBox = ref new TextBox();
        roomNumberTextBox->Header = "Room Number and Building:";

        auto comboBox_physProbSelector = ref new ComboBox();
        comboBox_physProbSelector->Header = "Problem:";
        auto comboBox_digiProbSelector = ref new ComboBox();
        comboBox_digiProbSelector->Header = "Problem:";

        // grab all possible ticket options
        if (grabbedTicketData.is_open())
        {
            std::string line;
            while (std::getline(grabbedTicketData, line))
            {
                if (line == "_START_TYPE_TICK")
                {
                    GrabOptionFromFile(grabbedTicketData, "_END_TYPE_TICK", comboBox_typeSelector);
                }
                else if (line == "_START_LOC_PHYS")
                {
                    GrabOptionFromFile(grabbedTicketData, "_END_LOC_PHYS", comboBox_placeSelector);
                }
                else if (line == "_START_PROB_PHYS")
                {
                    GrabOptionFromFile(grabbedTicketData, "_END_PROB_PHYS", comboBox_physProbSelector);
                }
                else if (line == "_START_PROB_DIGI")
                {
                    GrabOptionFromFile(grabbedTicketData, "_END_PROB_DIGI", comboBox_digiProbSelector);
                }
            }
        }
        else
        {
            comboBox_placeSelector->Items->Append("Error: Unable to load ticket options file");
        }

        comboBox_typeSelector->SelectedIndex = 0;
        comboBox_placeSelector->SelectedIndex = 0;
        comboBox_physProbSelector->SelectedIndex = 0;
        comboBox_digiProbSelector->SelectedIndex = 0;

        comboBox_typeSelector->SelectionChanged += ref new SelectionChangedEventHandler(
            [comboBox_physProbSelector, comboBox_digiProbSelector, comboBox_placeSelector, roomNumberTextBox](Object^ sender, SelectionChangedEventArgs^ e)
            {
                // get the current choice
                //auto selectedItem = dynamic_cast<Platform::String^>(dynamic_cast<ComboBox^>(sender)->SelectedItem);
                auto comboBox = dynamic_cast<ComboBox^>(sender);
                int selectedIndex = comboBox->SelectedIndex;

                // toggle visibility of unneeded items depending on selection
                if (selectedIndex == 1)
                {
                    // show physical only
                    comboBox_placeSelector->Visibility = Windows::UI::Xaml::Visibility::Visible;
                    roomNumberTextBox->Visibility = Windows::UI::Xaml::Visibility::Visible;
                    comboBox_physProbSelector->Visibility = Windows::UI::Xaml::Visibility::Visible;
                    comboBox_digiProbSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                }
                else if (selectedIndex == 2)
                {
                    // show digital only
                    comboBox_placeSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                    roomNumberTextBox->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                    comboBox_physProbSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                    comboBox_digiProbSelector->Visibility = Windows::UI::Xaml::Visibility::Visible;
                }
                else
                {
                    // (default) hide both
                    comboBox_placeSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                    roomNumberTextBox->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                    comboBox_physProbSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                    comboBox_digiProbSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
                }
            });

        // hide everything by default
        comboBox_placeSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        roomNumberTextBox->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        comboBox_physProbSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
        comboBox_digiProbSelector->Visibility = Windows::UI::Xaml::Visibility::Collapsed;

        panel->Children->Append(comboBox_typeSelector);
        panel->Children->Append(comboBox_placeSelector);
        panel->Children->Append(comboBox_physProbSelector);
        panel->Children->Append(comboBox_digiProbSelector);
        panel->Children->Append(roomNumberTextBox);

        // ticket description
        auto descriptionTextBox = ref new TextBox();
        descriptionTextBox->Header = "Description:";
        descriptionTextBox->PlaceholderText = "Enter a brief description of the ticket";
        descriptionTextBox->AcceptsReturn = true;
        panel->Children->Append(descriptionTextBox);

        // finish dialog box building
        dialog->Content = panel;
        dialog->PrimaryButtonText = "Submit";
        dialog->CloseButtonText = "Cancel";

        dialog->PrimaryButtonClick += ref new TypedEventHandler<ContentDialog^, ContentDialogButtonClickEventArgs^>(
            [this, titleTextBox, descriptionTextBox](ContentDialog^ sender, ContentDialogButtonClickEventArgs^ args)
            {
                Calendar^ calendarForTicket = ref new Calendar();
                Platform::String^ currentDate = calendarForTicket->MonthAsPaddedNumericString(2) + "/"
                                                + calendarForTicket->DayAsPaddedString(2) + "/"
                                                + calendarForTicket->YearAsString();

                auto new_ticket = ref new TicketItem("You", titleTextBox->Text, currentDate, descriptionTextBox->Text);
                contained_tickets->Append(new_ticket);
            });

        // now show dialog (and close file)
        grabbedTicketData.close();
        dialog->ShowAsync();
    }

    void MainPage::NewComment_Click(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
    {
        auto selected_ticket = dynamic_cast<TicketItem^>(InboxSidePanel->SelectedItem);
        
        // if no ticket selected
        if (selected_ticket == nullptr)
        {
            auto noTicketMessage = ref new Windows::UI::Xaml::Controls::ContentDialog();
            noTicketMessage->Title = "Select a ticket";
            noTicketMessage->Content = "Please select a ticket from the sidebar before adding a comment.";
            noTicketMessage->CloseButtonText = "OK";
            noTicketMessage->ShowAsync();
            return;
        }

        // make the dialog box
        auto commentDialog = ref new Windows::UI::Xaml::Controls::ContentDialog();
        commentDialog->Title = "New Comment";
        auto panel = ref new StackPanel();

        // main comment box
        auto commentTextBox = ref new TextBox();
        commentTextBox->Header = "Comment:";
        commentTextBox->PlaceholderText = "Enter your comment here...";
        panel->Children->Append(commentTextBox);

        commentDialog->Content = panel;
        commentDialog->PrimaryButtonText = "Submit";
        commentDialog->CloseButtonText = "Cancel";

        // define the ticket we're adding a comment to
        commentDialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<
            Windows::UI::Xaml::Controls::ContentDialog^,
            Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^>(
                [this, selected_ticket, commentTextBox](Windows::UI::Xaml::Controls::ContentDialog^ sender,
                    Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
                {
                    Calendar^ calendarForTicket = ref new Calendar();
                    Platform::String^ currentDate = calendarForTicket->MonthAsPaddedNumericString(2) + "/"
                                                    + calendarForTicket->DayAsPaddedString(2) + "/"
                                                    + calendarForTicket->YearAsString();
                    
                    auto newComment = ref new TicketComment("You", commentTextBox->Text, currentDate);
                    selected_ticket->OurComments->Append(newComment);
                });

        // now show pop-up
        commentDialog->ShowAsync();
    }
}