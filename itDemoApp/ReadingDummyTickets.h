#pragma once
#include <pch.h>
#include <MainPage.xaml.h>

// this function exists because i'd rather not reimplement a similar method as seen in the new ticket function
// hardcoded data is a womp womp, but it's whatever
inline void get_the_dummy_data(Platform::Collections::Vector<itDemoApp::TicketItem^>^ input_email_list)
{
	/// item #1
	input_email_list->Append(ref new itDemoApp::TicketItem(
		"Lewis Anderson, You",
		"Broken or damaged computer accessory",
		"03/10/2025",
		"I dropped our mice while I was on the way to my car the other day and it fell into a puddle. I plugged it in later after I got home and it wasn't working. Whoops. :("
	));
	/// comment #1 for item #1
	input_email_list->GetAt(0)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Andrew Woods",
		"Don't sweat it, it happens! Stop by the IT office with those mice and come pick up some new ones.",
		"03/10/2025"
	));



	/// item #2
	input_email_list->Append(ref new itDemoApp::TicketItem(
		"Elizabeth Burke, You",
		"Screen not appearing on TV or projector",
		"03/08/2025",
		"My projector occasionally flickered throughout today but now it finally stopped working in my last class."
	));
	/// comment #1 for item #2
	input_email_list->GetAt(1)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Preston Flynn",
		"Did you check the cables between the computer? Is the HDMI cable plugged in and not wobbly?",
		"03/08/2025"
	));
	/// comment #2 for item #2
	input_email_list->GetAt(1)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Elizabeth Burke",
		"Yes, I did check that this morning.That cable is plugged in and good, I believe.",
		"03/08/2025"
	));
	/// comment #3 for item #2
	input_email_list->GetAt(1)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Preston Flynn",
		"I'll be there tomorrow morning to check on it.",
		"03/08/2025"
	));
	/// comment #4 for item #2
	input_email_list->GetAt(1)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Preston Flynn",
		"Computer and cables are good, but projector bulb died. I'll send this to maintenance.",
		"03/09/2025"
	));
	/// comment #5 for item #2
	input_email_list->GetAt(1)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Kendyl Simmons",
		"Replaced the bulb and is now working again.",
		"03/09/2025"
	));
	/// comment #6 for item #2
	input_email_list->GetAt(1)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Elizabeth Burke",
		"Thank you so much!",
		"03/09/2025"
	));



	/// item #3
	input_email_list->Append(ref new itDemoApp::TicketItem(
		"You",
		"Computer is out of date",
		"03/12/2025",
		"I can't use Chrome on the laptop you gave to me. YouTube says my browser is out of date?"
	));
	/// comment #1 for item #3
	input_email_list->GetAt(2)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Andrew Woods",
		"It didn't update automatically?",
		"03/12/2025"
	));
	/// comment #2 for item #3
	input_email_list->GetAt(2)->OurComments->Append(ref new itDemoApp::TicketComment(
		"You",
		"It says my OS is not supported? This computer has Windows 7.",
		"03/12/2025"
	));
	/// comment #3 for item #3
	input_email_list->GetAt(2)->OurComments->Append(ref new itDemoApp::TicketComment(
		"Andrew Woods",
		"That's odd. I thought we got rid of all those devices. Stop by the office and we'll give you a new one.",
		"03/12/2025"
	));
}