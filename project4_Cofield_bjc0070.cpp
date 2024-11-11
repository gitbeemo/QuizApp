//=============================================================================
// Author      : Benjamin Cofield
// Compile     : g++ project4_Cofield_bjc0070.cpp -o Project4.out
// Run         : ./Project4.out
//=============================================================================

#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Structures */
struct Choice {
	string text;
	Choice* next;
};

struct Question {
	string question;           // The question text
	string type;
	string correctAnswer;
	string userAnswer;
	double pointValue;
	bool answered;
	Choice* choices;

	Question() : answered(false), choices(nullptr) {}
};

struct Node {
	Question question;
	Node* next;
	bool answered;
};


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Create */
Choice* createChoice(const std::string& choiceText) {
	Choice* newChoice = new Choice;
	newChoice->text = choiceText;
	newChoice->next = nullptr;
	return newChoice;
}

Node* createNode(const Question& q) {
	Node* newNode = new Node;
	newNode->question = q;
	newNode->next = nullptr;
	return newNode;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Add MCQ Choice */
void addChoice (Question& q) {
	string choiceText;
	bool hasChoice = false;
	Choice* lastChoice = nullptr;
	for (int i = 0; i < 10; ++i) {
		cout << "Enter choice " << char('A' + i) << ": ";
		getline(cin, choiceText);
		if (choiceText == "quit()" && hasChoice) {
			break;
		} else if (choiceText == "quit()" && !hasChoice) {
			cout << "Add one choice before quitting.\n";
			--i;
			continue;
		}
		Choice* newChoice = createChoice(choiceText);

		if (!q.choices) {
			// If first choice, set as head
			q.choices = newChoice;
		} else {
			lastChoice-> next = newChoice; //Append at the end
		}


		lastChoice = newChoice;
		hasChoice = true;
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to check correct answer for MCQ */
bool isCorrectAnswer(Question& q, const string& correctAnswer) {
	Choice* current = q.choices;
	char correctChar = tolower(correctAnswer[0]);
	char allowedChar = 'a';
	while (current != nullptr) {
		if (correctChar == allowedChar) return true;
		current = current->next;
		++allowedChar;
	}
	return false;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to add a question to linked list */

// Helper Functions

string getQuestionType(string qType) {
	if (qType.empty()) {
		while (true) {
			cout << "Type of question [mcq/tf/wr]: ";
			cin >> qType;
			if (qType == "mcq" || qType == "tf" || qType == "wr") break;
			cout << "[Command not recognized, please try again!]\n\n";
		}
	}
	return qType;
}

string promptForQuestionText() {
	cout << "Enter a question: ";
	string text;
	getline(cin, text);
	return text;
}

string promptForCorrectAnswerMCQ(Question& q) {
	string answer;
	while (true) {
		cout << "Select correct answer: ";
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		if (isCorrectAnswer(q, answer)) break;
		cout << "[Answer not recognized, please try again!]\n";
	}
	return answer;
}

string promptForCorrectAnswerTF() {
	string answer;
	while (true) {
		cout << "Select correct answer [true/false]: ";
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		if (answer == "true" || answer == "false") break;
		cout << "[Answer not recognized, please try again!]\n";
	}
	return answer;
}

string promptForCorrectAnswerWR() {
	cout << "Type correct answer: ";
	string answer;
	getline(cin, answer);
	return answer;
}

double promptForPointValue() {
	double points;
	while (true) {
		cout << "Enter point value: ";
		if (cin >> points && points > 0) break;
		cout << "[Invalid point value, please try again!]\n";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return points;
}

void nonInteractiveaddQuestion(Node*& head, const string& type, const string& questionText, const string& correctAnswer, double pointValue) {
	Question q;
	q.choices = nullptr;  // Initialize the choices pointer
	q.type = type;
	q.question = questionText;
	q.correctAnswer = correctAnswer;
	q.pointValue = pointValue;

	// Since choices are only needed for MCQ, we can skip this part for other types of questions.
	if (q.type == "mcq") {
		// Manually add choices here for the MCQ case, if needed.
	}

	// Create new node
	Node* newNode = createNode(q);
	newNode->next = nullptr;  // New node points to null (end of the list)

	// If the list is empty, the new node becomes the head
	if (head == nullptr) {
		head = newNode;
	} else {
		// Otherwise, find the last node and append the new node
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}


void addQuestion(Node*& head, const string& type = "", const string& questionText = "", const string& correctAnswer = "", double pointValue = 0.0) {
    Question q;
    q.choices = nullptr;  // Initialize the choices pointer

    // If we're testing, we can directly pass the question type and text
    if (!type.empty()) {
        q.type = type;
        q.question = questionText;
        q.correctAnswer = correctAnswer;
        q.pointValue = pointValue;
    } else {
        // For normal usage, prompt the user for input
        while (true) {
            cout << "Type of question [mcq/tf/wr]: ";
            cin >> q.type;
            if (q.type == "mcq" || q.type == "tf" || q.type == "wr") {
                break;
            } else {
                cout << "[Command not recognized, please try again!]\n\n";
            }
        }
        cin.ignore();

        cout << "Enter a question: ";
        getline(cin, q.question);

        // Handling MCQ questions
        if (q.type == "mcq") {
            cout << "[At any time, type 'quit()' to exit]\n";
            addChoice(q);
            while (true) {
                cout << "Select correct answer: ";
                cin >> q.correctAnswer;
                transform(q.correctAnswer.begin(), q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);

                if (isCorrectAnswer(q, q.correctAnswer)) {
                    break;
                }
                cout << "[Answer not recognized, please try again!]\n";
            }
            transform(q.correctAnswer.begin(), q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);

        } else if (q.type == "tf") {
            while (true) {
                cout << "Select correct answer: ";
                cin >> q.correctAnswer;
                transform(q.correctAnswer.begin(), q.correctAnswer.end(), q.correctAnswer.begin(), ::tolower);
                if (q.correctAnswer == "true" || q.correctAnswer == "false") {
                    break;
                }
                cout << "[Answer not recognized, please try again!]\n";
            }
        } else if (q.type == "wr") {
            cout << "Type correct answer: ";
            getline(cin, q.correctAnswer);
        }

        cout << "Enter point value: ";
        while (!(cin >> q.pointValue) || q.pointValue <= 0.0) {
            cout << "[Not a valid point value, please try again!]\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter point value: ";
        }
        cin.ignore();
    }

    // Create new node and add it to the list
    Node* newNode = createNode(q);
    newNode->next = head;  // Point new node to the previous head
    head = newNode;        // Update head to the new node
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to add a edit questions from a linked list */
void editQuestion(Node* head) {
	// Pull total questions
	int totalQuestions = 0;
	Node* current = head;
	while (current != nullptr) {
		totalQuestions++;
		current = current->next;
	}

	string input;
	int questionNumber = -1;

	// Prompt until valid input or "quit()" is entered
	while (true) {
		cout << "Select a question to edit, or type quit() [1-" << totalQuestions << "]: ";
		cin >> input;
		cin.ignore();

		if (input == "quit()") {
			return;
		}

		try {
			questionNumber = stoi(input);
			if (questionNumber >= 1 && questionNumber <= totalQuestions) {
				break; // Valid input, exit loop
			} else {
				cout << "[That question does not exist! Try again.]\n";
			}
		} catch (invalid_argument&) {
			cout << "[Invalid input! Please enter a valid question number or quit().]\n";
		}
	}

	// Go to selected question
	current = head;
	for (int i = 1; i < questionNumber && current != nullptr; i++) {
		current = current->next;
	}

	if (current != nullptr) {
		cout << "===============================\n"
			 << "=== QUESTION " << questionNumber << " ===\n"
			 << "===============================\n";
		cout << "1. Type: " << current->question.type << "\n";
		cout << "2. Question: " << current->question.question << "\n";
		cout << "3. Answer choices:\n";

		// Display answer choices if type is "mcq"
		if (current->question.type == "mcq") {
			Choice* choice = current->question.choices;
			char option = 'A';
			while (choice != nullptr) {
				cout << option << ". " << choice->text << endl;
				choice = choice->next;
				++option;
			}
		} else {
			cout << "    [No choices available for this question type.]\n";
		}

		cout << "4. Correct answer: " << current->question.correctAnswer << "\n";

		// Edit specific fields
		cout << "Type a number to edit, or type quit(): ";
		cin >> input;
		cin.ignore();

		if (input == "quit()") {
			return;
		}

		try {
			int fieldToEdit = stoi(input);

			if (fieldToEdit == 1) {
				cout << "Enter a new question type: ";
				cin >> current->question.type;
				cin.ignore();
			} else if (fieldToEdit == 2) {
				cout << "Enter a new question: ";
				getline(cin, current->question.question);
			} else if (fieldToEdit == 3 && current->question.type == "mcq") {
				Choice* choice = current->question.choices;
				char option = 'A';
				while (choice != nullptr) {
					cout << "Enter new text for choice " << option << ": ";
					getline(cin, input);
					if (input == "quit()") {
						return;
					}
					choice->text = input;
					choice = choice->next;
					++option;
				}
			} else if (fieldToEdit == 3) {
				cout << "[No choices to edit for this question type.]\n";
			} else if (fieldToEdit == 4) {
				cout << "Enter new correct answer: ";
				getline(cin, current->question.correctAnswer);
			} else {
				cout << "[Not recognized. No changes made.]\n";
			}
		} catch (invalid_argument&) {
			cout << "[Invalid input! Please enter a valid option number or quit().]\n";
		}
	} else {
		cout << "[No such question exists!]\n";
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Function to delete a question from a  linked list */
void deleteQuestion(Node*& head) {
	// Pull total questions
	int totalQuestions = 0;
	Node* current = head;
	while (current != nullptr) {
		totalQuestions++;
		current = current->next;
	}

	int questionNumber;
	cout << "Select a question to delete [1-" << totalQuestions << "]: ";
	cin >> questionNumber;
	cin.ignore();

	if (questionNumber <= 0) {
		cout << "[That question does not exist!]\n";
		return;
	}

	current = head;
	Node* previous = nullptr;
	for (int i = 1; i < questionNumber && current != nullptr; ++i) {
		previous = current;
		current = current->next;
	}

	if (current != nullptr) {
		if (previous == nullptr) {
			head = current->next;
		} else {
			previous->next = current->next;
		}
		delete current;
		cout << "Question " << questionNumber << " deleted.\n";
	} else {
		cout << "[No such question exists!]\n";
	}
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Display Session Log */
void displaySessionLog(Node*& head) {
	Node* current = head;
	int totalQuestions = 0;
	double totalPointValues = 0.0;

	cout << "=== Session Log ===\n";
	while (current != nullptr) {
		totalQuestions++;
		totalPointValues += current -> question.pointValue;
		current = current -> next;
	}


	cout << "Total questions: " << totalQuestions;
	cout << "\nTotal point values: " << totalPointValues;
	cout << "\n\n";
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Reverse list back to its order */
void reverseList(Node*& head) {
	Node* prev = nullptr;
	Node* current = head;
	Node* next = nullptr;
	while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Assessment */
void startAssessment(Node* head) {
    double totalPoints = 0.0, score = 0.0;
    int totalQuestions = 0, correctQuestions = 0;
    int qNumber = 1;

    // Gather total points and question count
    Node* temp = head;
    while (temp != nullptr) {
        totalPoints += temp->question.pointValue;
        totalQuestions++;
        temp = temp->next;
    }

    Node* current = head;
    int currentQuestionIndex = 0;
    string input;

    cout << "<!> Begin assessment? [y/n]: ";
    cin >> input;
    if (input != "y") return;

    while (true) {
        // Find the current question node
        Node* questionNode = head;
        for (int i = 0; i < currentQuestionIndex; ++i) {
            questionNode = questionNode->next;
        }

        // Display the question
        cout << "\nQuestion " << currentQuestionIndex + 1 << ": " << questionNode->question.question << endl;

        // Display choices for MCQ type questions
        if (questionNode->question.type == "mcq") {
            Choice* choice = questionNode->question.choices;
            char option = 'A';
            while (choice != nullptr) {
                cout << option << ". " << choice->text << endl;
                choice = choice->next;
                ++option;
            }
        }

        // Input answer
        cout << "Your answer: ";
        if (questionNode->question.type == "wr") {
            cin.ignore();
            getline(cin, questionNode->question.userAnswer);
        } else {
            cin >> questionNode->question.userAnswer;
            cin.ignore();
        }

        // Convert answer to lowercase
        transform(questionNode->question.userAnswer.begin(), questionNode->question.userAnswer.end(), questionNode->question.userAnswer.begin(), ::tolower);

        // Mark question as answered
        questionNode->answered = !questionNode->question.userAnswer.empty();

        // Check if all questions are answered
        bool allAnswered = true;
        temp = head;
        while (temp != nullptr) {
            if (!temp->answered) {
                allAnswered = false;
                break;
            }
            temp = temp->next;
        }

        // Action menu
        while (true) {
            if (allAnswered) {
                cout << "All questions answered. Do you want to?\n1. Edit an answer.\n2. Submit.\nSelect an action: ";
            } else {
                cout << "Do you want to?\n1. Go to next unanswered question.\n2. Jump to question.\n3. Submit.\nSelect an action: ";
            }

            cin >> input;

            if (input == "1") { // Go to next unanswered question or edit answer if all are answered
                if (allAnswered) {
                    int editQuestion;
                    cout << "Select question number to edit [1-" << totalQuestions << "]: ";
                    cin >> editQuestion;
                    if (editQuestion >= 1 && editQuestion <= totalQuestions) {
                        currentQuestionIndex = editQuestion - 1;
                        break;
                    } else {
                        cout << "[Invalid question number!]\n";
                    }
                } else {
                    // Move to next unanswered question
                    Node* nextNode = head;
                    int nextIndex = 0;
                    bool foundUnanswered = false;
                    for (int i = 0; i < totalQuestions; i++) {
                        if (!nextNode->answered) {
                            foundUnanswered = true;
                            currentQuestionIndex = nextIndex;
                            break;
                        }
                        nextNode = nextNode->next;
                        nextIndex++;
                    }
                    if (!foundUnanswered) {
                        cout << "All questions have been answered. Moving to the next question in sequence.\n";
                        currentQuestionIndex = (currentQuestionIndex + 1) % totalQuestions;
                    }
                    break;
                }
            } else if (input == "2") { // Jump to specific question
                if (allAnswered) { // If all questions are answered, treat option 2 as "Submit"
                    cout << "/!\\ Assessment Complete.\n";
                    cout << "=== SESSION LOG ===\n";
                    correctQuestions = 0;
                    score = 0.0;

                    // Display session log and calculate score
                    temp = head;
                    while (temp != nullptr) {
                        cout << "Question " << qNumber << ": " << temp->question.question << endl;
                        cout << "Correct answer: " << temp->question.correctAnswer << endl;
                        cout << "Your answer: " << temp->question.userAnswer << endl;

                        if (temp->question.userAnswer == temp->question.correctAnswer) {
                            cout << "[Correct]\n";
                            score += temp->question.pointValue;
                            correctQuestions++;
                        } else {
                            cout << "[Incorrect]\n";
                        }

                        temp = temp->next;
                        qNumber++;
                    }

                    cout << "Correct answers: " << correctQuestions << "/" << totalQuestions << endl;
                    cout << "Final score: " << score << "/" << totalPoints << endl;
                    cout << "*** Thank you for using the testing service. Goodbye! ***\n";
                    return;
                }

                int jumpTo;
                cout << "Jump to question [1-" << totalQuestions << "]: ";
                cin >> jumpTo;
                if (jumpTo >= 1 && jumpTo <= totalQuestions) {
                    currentQuestionIndex = jumpTo - 1;
                    questionNode = head;
                    for (int i = 0; i < currentQuestionIndex; ++i) {
                        questionNode = questionNode->next;
                    }

                    cout << "You answered: " << questionNode->question.userAnswer << endl;
                    cout << "Do you want to edit this answer? [y/n]: ";
                    cin >> input;

                    if (input == "y") {
                        cout << "New answer: ";
                        if (questionNode->question.type == "wr") {
                            cin.ignore(); // ignore any leftover newline character
                            getline(cin, questionNode->question.userAnswer);
                        } else {
                            cin >> questionNode->question.userAnswer;
                            cin.ignore(); // clear any extra newline
                        }
                    }

                    // After editing or not editing, return to the menu prompt
                    break;
                } else {
                    cout << "[Invalid question number!]\n";
                }
            } else if (input == "3" || (allAnswered && input == "2")) { // Submit assessment
                if (!allAnswered) {
                    cout << "Some questions are unanswered. Are you sure you want to submit? [y/n]: ";
                    cin >> input;
                    if (input != "y") continue;
                }

                cout << "/!\\ Assessment Complete.\n";
                cout << "=== SESSION LOG ===\n";
                correctQuestions = 0;
                score = 0.0;

                // Display session log and calculate score
                temp = head;
                while (temp != nullptr) {
                    cout << "Question " << qNumber << ": " << temp->question.question << endl;
                    cout << "Correct answer: " << temp->question.correctAnswer << endl;
                    cout << "Your answer: " << temp->question.userAnswer << endl;

                    if (temp->question.userAnswer == temp->question.correctAnswer) {
                        cout << "[Correct]\n";
                        score += temp->question.pointValue;
                        correctQuestions++;
                    } else {
                        cout << "[Incorrect]\n";
                    }

                    temp = temp->next;
                    qNumber++;
                }

                cout << "Correct answers: " << correctQuestions << "/" << totalQuestions << endl;
                cout << "Final score: " << score << "/" << totalPoints << endl;
                cout << "*** Thank you for using the testing service. Goodbye! ***\n";
                return;
            } else {
                cout << "[Invalid action selected! Try again.]\n";
            }
        }
    }
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Test Drivers */

#ifdef UNIT_TESTING
#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

using namespace std;

// Assuming your structs (Node, Question, Choice) and necessary helper functions are defined

void testDriver() {
    Node* head = nullptr;

    // Unit Test Case 1: Add a written response (WR) question to an empty list
    cout << "Unit Test Case 1: Add a written response (WR) question to an empty list." << endl;
    nonInteractiveaddQuestion(head, "wr", "What is the capital of France?", "Paris", 5.0);
    cout << "Added Question 1: " << head->question.question << endl;  // Print for debugging
    assert(head != nullptr);  // Ensure head is not null
    assert(head->question.question == "What is the capital of France?");  // Check if the question is correct
    cout << "Test Case 1 Passed." << endl << endl;

    // Unit Test Case 2: Add a multiple-choice (MCQ) question to the list
    cout << "Unit Test Case 2: Add a multiple-choice (MCQ) question to the list." << endl;
    nonInteractiveaddQuestion(head, "mcq", "What is 2 + 2?", "4", 10.0);
    cout << "Added Question 2: " << head->next->question.question << endl;  // Print for debugging
    assert(head->next != nullptr);  // Ensure the next question exists
    assert(head->next->question.question == "What is 2 + 2?");  // Ensure the second question is correct
    cout << "Test Case 2 Passed." << endl << endl;

    // Unit Test Case 3: Add another multiple-choice (MCQ) question
    cout << "Unit Test Case 3: Add another multiple-choice (MCQ) question." << endl;
    nonInteractiveaddQuestion(head, "mcq", "What is the largest planet in the solar system?", "Jupiter", 20.0);
    cout << "Added Question 3: " << head->next->next->question.question << endl;  // Print for debugging
    assert(head->next->next != nullptr);  // Ensure the third question exists
    assert(head->next->next->question.question == "What is the largest planet in the solar system?");  // Ensure the third question is correct
    cout << "Test Case 3 Passed." << endl << endl;

    // Unit Test Case 4: Add a true/false (TF) question
    cout << "Unit Test Case 4: Add a true/false (TF) question." << endl;
    nonInteractiveaddQuestion(head, "tf", "Is the sky blue?", "true", 5.0);
    cout << "Added Question 4: " << head->next->next->next->question.question << endl;  // Print for debugging
    assert(head->next->next->next != nullptr);  // Ensure the fourth question exists
    assert(head->next->next->next->question.question == "Is the sky blue?");  // Ensure the fourth question is correct
    cout << "Test Case 4 Passed." << endl << endl;

    // Unit Test Case 5: Check the entire list of questions
    cout << "Unit Test Case 5: Check the entire list of questions." << endl;
    Node* temp = head;
    int count = 1;
    while (temp != nullptr) {
        cout << "Question " << count++ << ": " << temp->question.question << endl;
        temp = temp->next;
    }
    cout << "Test Case 5 Passed." << endl << endl;

    // Unit Test Case 6: Verify the first question's next is not null after multiple additions
    cout << "Unit Test Case 6: Verify the first question's next is not null after multiple additions." << endl;
    assert(head->next != nullptr);  // Ensure the first question's next is not null
    assert(head->next->question.question == "What is 2 + 2?");  // Ensure the second question is correct
    cout << "Test Case 6 Passed." << endl << endl;
}

#endif
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/* Main Function */
int main () {
	#ifdef UNIT_TESTING
	testDriver();
	#else
	Node* head = nullptr; // init the node ptr
	int choice;
	bool exitProgram = false;

	cout << "*** Welcome to Ben's Testing Service ***\n\n";

	do {
		cout << "Do you want to?\n" <<
			"  1. Create new question.\n" <<
			"  2. Edit question.\n" <<
			"  3. Delete question.\n" <<
			"  4. Finish.\n";
		cout << "Select an action: ";
		cin >> choice;
		cin.ignore();

		switch(choice) {
			case 1:
				addQuestion(head);
				cout << "Question saved.\n\n";
				break;;
			case 2:
				editQuestion(head);
				break;
			case 3:
				deleteQuestion(head);
				break;
			case 4:
				displaySessionLog(head);
				exitProgram = true;
				break;

		}
	} while (!exitProgram);

	//Start the Assessment
	reverseList(head);
	startAssessment(head);

	cout << "*** Thank you for using the testing service. Goodbye! ***";
	#endif
	return 0;
}
