#include <iostream>
#include <thread> 
#include <chrono> 
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to display the question and options with a timer and lifelines
bool askQuestion(string question, string options[], char correctOption, int timeLimit, bool &used50_50, bool &usedPhoneAFriend, bool &usedAudiencePoll, bool &usedAskTheExpert)
{
    char userInput = '\0';
    bool answered = false;

    // Timer thread to display countdown
    thread timerThread([&]()
                       {
        for (int i = timeLimit; i > 0; --i) {
            cout << "\rTime left: " << i << " seconds ";
            cout.flush();
            this_thread::sleep_for(chrono::seconds(1));
            if (answered) {
                return;
            }
        }
        cout << "\nTime's up!\n"; });

    // Display question and options
    cout << "\n"
         << question << endl;
    for (int i = 0; i < 4; ++i)
    {
        cout << (char)('A' + i) << ". " << options[i] << endl;
    }

    // Display available lifelines
    cout << "Lifelines available:\n";
    if (!used50_50)
        cout << "1. 50-50\n";
    if (!usedPhoneAFriend)
        cout << "2. Phone a Friend\n";
    if (!usedAudiencePoll)
        cout << "3. Audience Poll\n";
    if (!usedAskTheExpert)
        cout << "4. Ask the Expert\n";

    // Capture user input for lifelines or answer
    while (true)
    {
        if (_kbhit())
        {
            userInput = toupper(_getch()); // Capture user input

            // 50-50 Lifeline
            if (userInput == '1' && !used50_50)
            {
                used50_50 = true;
                cout << "\nUsing 50-50 lifeline...\n";
                int removed = 0;
                srand(time(0));
                for (int i = 0; i < 4; ++i)
                {
                    if (options[i][0] != correctOption && removed < 2)
                    {
                        options[i] = "----"; // Hide two incorrect options
                        removed++;
                    }
                }
                // Display updated options
                for (int i = 0; i < 4; ++i)
                {
                    if (options[i] != "----")
                    {
                        cout << (char)('A' + i) << ". " << options[i] << endl;
                    }
                }
                continue; // Allow user to answer after using a lifeline
            }
            // Phone a Friend Lifeline
            else if (userInput == '2' && !usedPhoneAFriend)
            {
                usedPhoneAFriend = true;
                cout << "\nPhone a Friend: I think the correct answer might be " << correctOption << ".\n";
                continue; // Allow user to answer after using a lifeline
            }
            // Audience Poll Lifeline
            else if (userInput == '3' && !usedAudiencePoll)
            {
                usedAudiencePoll = true;
                cout << "\nAudience Poll: Most of the audience thinks the answer is " << correctOption << ".\n";
                continue; // Allow user to answer after using a lifeline
            }
            // Ask the Expert Lifeline
            else if (userInput == '4' && !usedAskTheExpert)
            {
                usedAskTheExpert = true;
                cout << "\nAsk the Expert: Based on my knowledge, I believe the answer is " << correctOption << ".\n";
                continue; // Allow user to answer after using a lifeline
            }
            // User chose an answer
            else if (userInput >= 'A' && userInput <= 'D')
            {
                answered = true;
                break;
            }
            else
            {
                cout << "\nInvalid input. Please choose a valid option or lifeline.\n";
            }
        }
    }

    // Wait for timer thread to complete
    timerThread.join();

    // Check if the answer is correct
    if (answered)
    {
        if (userInput == correctOption)
        {
            cout << "Correct!\n";
            return true;
        }
        else
        {
            cout << "Game over!!!\n";
            return false;
        }
    }
    return false; // If time's up, return false
}

int main()
{
    string questions[] = {
        "Who was the first President of independent India?",
        "Who is known as the 'Iron Man of India'?",
        "In which year did India gain independence?",
        "Which Mughal emperor built the Taj Mahal?",
        "Who is known as the 'Father of the Indian Constitution'?",
        "Which Indian state is the largest by area?",
        "What was the main objective of the Green Revolution in India?",
        "Who was the first Prime Minister of India?",
        "Which Indian leader initiated economic liberalization in 1991?",
        "Where was the Non-Cooperation Movement launched by Mahatma Gandhi?",
        "Which city is known as the 'Financial Capital of India'?",
        "What is the currency of India?",
        "In which year was the Goods and Services Tax (GST) implemented in India?"};

    string options[][4] = {
        {"Dr. Rajendra Prasad", "Mahatma Gandhi", "Jawaharlal Nehru", "Subhas Chandra Bose"},
        {"Mahatma Gandhi", "Sardar Vallabhbhai Patel", "Bhagat Singh", "Jawaharlal Nehru"},
        {"1945", "1947", "1950", "1948"},
        {"Akbar", "Shah Jahan", "Babur", "Aurangzeb"},
        {"Dr. Rajendra Prasad", "B.R. Ambedkar", "Sardar Patel", "Mahatma Gandhi"},
        {"Madhya Pradesh", "Maharashtra", "Uttar Pradesh", "Rajasthan"},
        {"To increase wheat production", "To promote organic farming", "To boost cotton production", "To enhance agricultural exports"},
        {"Lal Bahadur Shastri", "Indira Gandhi", "Jawaharlal Nehru", "Mahatma Gandhi"},
        {"Atal Bihari Vajpayee", "P. V. Narasimha Rao", "Manmohan Singh", "Lal Bahadur Shastri"},
        {"Delhi", "Mumbai", "Ahmedabad", "Chauri Chaura"},
        {"New Delhi", "Bangalore", "Mumbai", "Kolkata"},
        {"Dollar", "Rupee", "Euro", "Pound"},
        {"2015", "2017", "2016", "2018"}};

    char correctOptions[] = {'A', 'B', 'B', 'B', 'B', 'D', 'A', 'C', 'B', 'D', 'C', 'B', 'B'}; // Add more correct options as needed
    int timeLimit = 60;

    // Lifeline usage tracking
    bool used50_50 = false;
    bool usedPhoneAFriend = false;
    bool usedAudiencePoll = false;
    bool usedAskTheExpert = false;

    cout << "Welcome to the KBC Quiz Game!\n";
    cout << "You have " << timeLimit << " seconds to answer each question.\n";

    for (int i = 0; i < 13; ++i)
    {
        bool result = askQuestion(questions[i], options[i], correctOptions[i], timeLimit, used50_50, usedPhoneAFriend, usedAudiencePoll, usedAskTheExpert);
        if (!result)
        {
            cout << "Game over.... Try Again.....\n";
            break;
        }
    }

    cout << "Thank you for playing!\n";
    return 0;
}
