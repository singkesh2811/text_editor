#include <iostream>
#include <string>
#include <stack>
#include <fstream>
using namespace std;
struct undoc
{
    int linenum;
    string text;
    int cnum;
    int mline;
    int nline;
};

struct node
{
    string data;
    struct node *next;
};

class linked_list
{
private:
    node *head;
    node *tail;
    int numlines = 0;
    int next = 1;
    stack<undoc> undostack;

public:
    std::ofstream fout;
    linked_list()
    {
        int choice = -1;
        head = NULL;
        tail = NULL;
        int prevpage = 1;
        bool yes;
        while (choice != 0)
        {
        mainmenu:
            cout << "\t\t\t\t\t\t\t\tTEXT EDITOR\n"<< endl;
            cout << "1. Print the text" << endl;
            cout << "2. Insert the text in a line"<<endl;
            cout<<"3. Replace two lines"<<endl;
            cout<<"4. Delete a line" << endl;
            cout<<"5. Save the text in file"<<endl;
            cout<<"6. Open a .txt file"<<endl;
            cout<<"7. Undo a line"<<endl;
            cout<<"8. Move a line from one to another"<<endl;
            cout<<"9. Print the prev. page"<<endl;
            cout<<"10. Print the next page"<<endl;
            cout<<"\n\nTo exit, press 0" << endl;
            cin >> choice;
            cout << endl;
            if (choice == 1)
            {
                print();
                cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                cin >> yes;
                if (yes)
                    goto mainmenu;
                else
                {
                    char save;
                    cout << "\nDo you want to saveas your work before exiting?(Y/N)\n ";
                    cin >> save;
                    if (save == 'y' || save == 'Y')
                        saveall();
                    exit(0);
                }
             }
            else if (choice == 2)
            {
                int line;
                string data;
                cout << "Enter the line number :  ";
                cin >> line;
                cout << "Enter text : ";
                cin.ignore(1);
                getline(cin, data);
                data += "\n";
                if (line == 1)
                {
                    addhead(data);
                }
                else if (line > numlines)
                {
                    insertaway(data, line);
                }
                else if (line < numlines)
                {
                    insertbetween(data, line);
                }
                else if (line == numlines)
                {
                    int selection;
                    cout << "Enter 1 to replace the last line or 2 to insert a new line";
                    cin >> selection;
                    if (selection == 1)
                    {
                        replacetext(data, line);
                    }
                    else if (selection == 2)
                    {
                        addtail(data);
                    }
                }
                cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                cin >> yes;
                if (yes)
                    goto mainmenu;
                else
                {
                    char save;
                    cout << "\nDo you want to saveas your work before exiting?(Y/N)\n ";
                    cin >> save;
                    if (save == 'y' || save == 'Y')
                        saveall();
                    exit(0);
                }

            }
            else if (choice == 3)
            {
                int line;
                string data;
                cout << "Enter line number to replace : ";
                cin >> line;
                if (line > numlines)
                {
                    cout << "Line number exceeds total number of lines" << endl;
                }
                else
                {
                    cout << "Enter the text want to add : ";
                    cin >> data;
                    data += "\n";
                    replacetext(data, line);
                }
                cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                cin >> yes;
                if (yes)
                    goto mainmenu;

            }
            else if (choice == 4)
            {
                int line;
                cout << "Enter the line to delete : ";
                cin >> line;
                deleteLine(line);
                cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                cin >> yes;
                if (yes)
                    goto mainmenu;
                else
                {
                    char save;
                    cout << "\nDo you want to saveas your work before exiting?(Y/N)\n ";
                    cin >> save;
                    if (save == 'y' || save == 'Y')
                        saveall();
                    exit(0);
                }
            }
            else if (choice == 5)
            {
                 saveall();
            }
            else if (choice == 6)
            {
                node *current = head;
                node *next;
                while (current != NULL)
                {
                    next = current->next;
                    free(current);
                    current = next;
                }
                head = NULL;
                openfile();
            }
            else if (choice == 7)
            {
                if (undostack.empty())
                {
                    cout << "No text is inserted for undo" << endl;
                    cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                    cin >> yes;
                    if (yes)
                        goto mainmenu;
                    else
                    {
                        char save;
                        cout << "\nDo you want to save your work before exiting?(Y/N)\n ";
                        cin >> save;
                        if (save == 'y' || save == 'Y')
                            saveall();
                        exit(0);
                    }
                }
                else
                {
                    undo();

                    cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                    cin >> yes;
                    if (yes)
                        goto mainmenu;
                    else
                    {
                        char save;
                        cout << "\nDo you want to save your work before exiting?(Y/N)\n ";
                        cin >> save;
                        if (save == 'y' || save == 'Y')
                            saveall();
                        exit(0);
                    }
                }
            }
            else if (choice == 8)
            {
                int line1;
                int line2;
                cout << "Enter line 1 to swap : ";
                cin >> line1;
                cout << "Enter line 2 to swap : ";
                cin >> line2;
                move_two_lines(line1, line2);
                cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                cin >> yes;
                if (yes)
                    goto mainmenu;
                else
                {
                    char save;
                    cout << "\nDo you want to saveas your work before exiting?(Y/N)\n ";
                    cin >> save;
                    if (save == 'y' || save == 'Y')
                        saveall();
                    exit(0);
                }
            }
            else if (choice == 10)
            {
                if (prevpage * 10 > numlines)
                {
                    printapage(prevpage);
                    cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                    cin >> yes;
                    if (yes)
                        goto mainmenu;
                    else
                    {
                        char save;
                        cout << "\nDo you want to save your work before exiting?(Y/N)\n ";
                        cin >> save;
                        if (save == 'y' || save == 'Y')
                            saveall();
                        exit(0);
                    }
                }
            }
            else if (choice == 9)
            {
                if (prevpage <= 0)
                {
                    prevpage = 1;
                    printapage(1);

                    cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                    cin >> yes;
                    if (yes)
                        goto mainmenu;
                    else
                    {
                        char save;
                        cout << "\nDo you want to save your work before exiting?(Y/N)\n ";
                        cin >> save;
                        if (save == 'y' || save == 'Y')
                            saveall();
                        exit(0);
                    }
                }
                else if (prevpage == 1)
                {
                    prevpage--;
                    printapage(1);
                    cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                    cin >> yes;
                    if (yes)
                        goto mainmenu;
                    else
                    {
                        char save;
                        cout << "\nDo you want to save your work before exiting?(Y/N)\n ";
                        cin >> save;
                        if (save == 'y' || save == 'Y')
                            saveall();
                        exit(0);
                    }
                }
                else
                {
                    prevpage--;
                    printapage(prevpage);
                    cout << "\nPress 1 to go back to the main menu and 0 to exit: ";
                    cin >> yes;
                    if (yes)
                        goto mainmenu;
                    else
                    {
                        char save;
                        cout << "\nDo you want to save your work before exiting?(Y/N)\n ";
                        cin >> save;
                        if (save == 'y' || save == 'Y')
                            saveall();
                        exit(0);
                    }
                }
            }
        }
    }
    void addhead(string data)
    {
        if (head == NULL)
        {
            node *temp;
            temp = new node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            numlines++;
        }
        else
        {
            node *temp;
            temp = new node;
            temp->data = data;
            temp->next = NULL;
            temp->next = head;
            head = temp;
            numlines++;
        }
        undoc headadd;
        headadd.linenum = 1;
        headadd.cnum = 1;
        undostack.push(headadd);
    }

    void addtail(string data)
    {
        if (head == NULL)
        {
            node *temp;
            temp = new node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            numlines++;
        }
        else
        {
            node *temp;
            temp = new node;
            temp->data = data;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            numlines++;
        }
        undoc tailadd;
        tailadd.linenum = 1;
        tailadd.cnum = 8;
        undostack.push(tailadd);
    }

    void deletehead()
    {
        string store = head->data;
        node *temp = head;
        node *nextnode = head->next;
        head = nextnode;
        delete (temp);
        numlines--;
        undoc head_delete;
        head_delete.text = store;
        head_delete.linenum = 1;
        head_delete.cnum = 3;
        undostack.push(head_delete);
    }

    void deletetail()
    {
        node *temp = head;
        if (head == NULL)
        {
            cout << "Nothing to be deleted." << endl;
        }
        else if (head == tail)
        {
            temp = head;
            string store = temp->data;
            delete (temp);
            head = NULL;
            tail = NULL;
            numlines--;
            undoc delete_tail;
            delete_tail.text = store;
            delete_tail.linenum = 1;
            delete_tail.cnum = 7;
            undostack.push(delete_tail);
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string store = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            numlines--;
            undoc delete_tail;
            delete_tail.text = store;
            delete_tail.linenum = 1;
            delete_tail.cnum = 7;
            undostack.push(delete_tail);
        }
    }

    void helperadd_tail(string data)
    {
        if (head == NULL)
        {
            node *temp;
            temp = new node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            numlines++;
        }
        else
        {
            node *temp;
            temp = new node;
            temp->data = data;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            numlines++;
        }
    }

    void helperdelete_tail()
    {
        node *temp = head;
        if (head == NULL)
        {
            cout << "Nothing to be deleted." << endl;
        }
        else if (head == tail)
        {
            temp = head;
            string store = temp->data;
            delete (temp);
            head = NULL;
            tail = NULL;
            numlines--;
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            delete temp->next;
            temp->next = NULL;
            numlines--;
        }
    }

    void replacetext(string data, int line)
    {
        undoc re_line;
        if (numlines < line)
        {
            cout << "Line exceeds existing line" << endl;
        }
        else if (line == 0)
        {
            cout << "There's no line at 0" << endl;
        }
        else if (numlines >= line)
        {
            node *temp = head;
            int gol = 1;
            while (gol < line)
            {
                temp = temp->next;
                gol++;
            }
            string store = temp->data;
            temp->data = data;
           re_line.linenum = line;
           re_line.text = store;
           re_line.cnum = 4;
            undostack.push(re_line);
        }
    }

    void insertbetween(string data, int line)
    {
        if (line == 0)
        {
            cout << "There's no line 0" << endl;
        }
        else if (line == 1)
        {
            if (head == NULL)
            {
                node *temp;
                temp = new node;
                temp->data = data;
                temp->next = NULL;
                head = temp;
                tail = head;
                numlines++;
            }
            else
            {
                node *temp;
                temp = new node;
                temp->data = data;
                temp->next = NULL;
                temp->next = head;
                head = temp;
                numlines++;
            }
            undoc head_inserted;
            head_inserted.linenum = 1;
            head_inserted.cnum = 5;
            undostack.push(head_inserted);
        }
        else
        {
            node *prevnode = head;
            node *nextnode = head;
            node *temp = new node();
            temp->data = data;
            temp->next = NULL;
            int it = 2;
            while (it < line)
            {
                prevnode = prevnode->next;
                nextnode = nextnode->next;
                it++;
            }
            nextnode = nextnode->next;
            prevnode->next = temp;
            temp->next = nextnode;
            numlines++;
            undoc insertedInBetween;
            insertedInBetween.linenum = line;
            insertedInBetween.cnum = 6;
            undostack.push(insertedInBetween);
        }
    }

    void insertaway(string data, int line)
    {
        undoc inser_away;
        inser_away.linenum = 0;
        inser_away.cnum = 9;
        if (head == NULL)
        {
            while (numlines < line - 1)
            {
                helperadd_tail("\n");
                inser_away.linenum++;
            }

            helperadd_tail(data);
        }
        else
        {
            while (numlines < line - 1)
            {
                helperadd_tail("\n");
                inser_away.linenum++;
            }
            helperadd_tail(data);
        }
        undostack.push(inser_away);
    }

    void deleteLine(int line)
    {
        if (head == NULL)
        {
            cout << "No line exist" << endl;
        }
        else if (line==0)
        {
             cout << "There's no line at 0" << endl;
        }
        else if (head==tail)
        {
            node *temp = head;
            delete (temp);
            head = NULL;
            tail = NULL;
            numlines--;

        }
        else if (line == 1)
        {
            string store = head->data;
            node *temp = head;
            node *nextnode = head->next;
            head = nextnode;
            delete (temp);
            numlines--;
            undoc headRemoved;
            headRemoved.text = store;
            headRemoved.linenum = 1;
            headRemoved.cnum = 12;
            undostack.push(headRemoved);
        }
        else if (line == numlines)
        {
            node *temp = head;
            undoc deletedline;
            deletedline.cnum = 11;
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string store = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            numlines--;
            deletedline.text = store;
            deletedline.linenum = line;
            undostack.push(deletedline);
        }
        else if (line > numlines)
        {
            cout << "Line number enter exceeds ltotal lines" << endl;
        }
        else if (line < numlines)
        {
            undoc deletedline;
            deletedline.cnum = 10;
            node *prevnode = head;
            node *nextnode = head;
            node *temp = head;
            int it = 2;
            while (it < line)
            {
                prevnode = prevnode->next;
                nextnode = nextnode->next;
                it++;
            }
            nextnode = nextnode->next;
            temp = nextnode;
            nextnode = nextnode->next;
            prevnode->next = nextnode;
            string store = temp->data;
            delete (temp);
            numlines--;
            deletedline.text = store;
            deletedline.linenum = line;
            undostack.push(deletedline);
        }
    }

    void move_two_lines(int nline, int mline)
    {
        if (nline == 1)
        {
            string headText = head->data;
            deletehead();
            insertbetween(headText, mline);
        }
        else
        {
            node *temp = head;
            int it = 1;
            while (it < nline)
            {
                temp = temp->next;
                it++;
            }
            string dataSaved = temp->data;
            deleteLine(nline);
            insertbetween(dataSaved, mline);
        }
        undoc move_n_m;
        move_n_m.cnum = 2;
        move_n_m.nline = nline;
        move_n_m.mline = mline;
        undostack.push(move_n_m);
    }

    void printapage(int page_g)
    {
        node *temp = head;
        if (numlines < page_g * 11)
        {
            int it = 1;
            while (it < (page_g * 11) - 10)
            {
                temp = temp->next;
                it++;
            }
            for (int s = (page_g * 11) - 10; s <= numlines; s++)
            {
                cout << s << ") " << temp->data << endl;
                temp = temp->next;
            }
            cout << "PAGE " << page_g << "**********************************\n";
        }
        else if (numlines >= page_g * 11)
        {
            int it = 1;
            while (it < (page_g * 11) - 10)
            {
                temp = temp->next;
                it++;
            }
            for (int s = (page_g * 11) - 10; s <= page_g * 11; s++)
            {
                cout << s << ") " << temp->data << endl;
                temp = temp->next;
            }
            cout << "PAGE " << page_g << "**********************************\n";
        }
        else if (page_g * 11 > numlines)
        {
            cout << "Page number invalid" << endl;
        }
    }

    void openfile()
    {
        string filename;
        cout << "Enter the file name : ";
        cin >> filename;
        filename += ".txt";
        ifstream fin;
        fin.open(filename);
        string s;
        while (getline(fin, s))
        {
            addtail(s);
        }
        fin.close();
    }

    void undo()
    {
        undoc temp = undostack.top();
        if (temp.cnum == 1)
        {
            cout << "Added To head, removing from head" << endl;
            deletehead();
            undostack.pop();
        }
        else if (temp.cnum == 2)
        {
            cout << "Moved M to N, moving N to M" << endl;
            move_two_lines(temp.mline, temp.nline);
            undostack.pop();
        }
        else if (temp.cnum == 3)
        {
            cout << "Deleted head, replacing head" << endl;
            ;
            addhead(temp.text);
            undostack.pop();
        }
        else if (temp.cnum == 4)
        {
            cout << "Replaced line, replacing again" << endl;
            replacetext(temp.text, temp.linenum);
            undostack.pop();
        }
        else if (temp.cnum == 5)
        {
            cout << "Inserted to Head, removing from head" << endl;
            deletehead();
            undostack.pop();
        }
        else if (temp.cnum == 6)
        {
            cout << "Inserted in between, removing that line" << endl;
            deleteLine(temp.linenum);
            undostack.pop();
        }
        else if (temp.cnum == 7)
        {
            cout << "Deleted Tail, inserting again" << endl;
            addtail(temp.text);
            undostack.pop();
        }
        else if (temp.cnum == 8)
        {
            cout << "Added to tail, removing from tail" << endl;
            deletetail();
            undostack.pop();
        }
        else if (temp.cnum == 9)
        {
            int w = temp.linenum;
            while (w >= 0)
            {
                helperdelete_tail();
                w--;
            }
            undostack.pop();
        }
        else if (temp.cnum == 10)
        {
            cout << "Line deleted, inserting again" << endl;
            insertbetween(temp.text, temp.linenum);
            undostack.pop();
        }
        else if (temp.cnum == 11)
        {
            cout << "Last line deleted, inserting again" << endl;
            addtail(temp.text);
            undostack.pop();
        }
        else if (temp.cnum == 12)
        {
            cout << "First line deleted, inserting again" << endl;
            addhead(temp.text);
            undostack.pop();
        }
    }

    void print()
    {
        node *temp = head;
        int linePrinted = 1;
        int pagePrinted = 2;
        int choice;
        if (head == NULL)
        {
            cout << "no elements here, yay!" << endl;
        }
        else
        {
            while (temp != NULL)
            {
                if (linePrinted == 1)
                {
                    cout << "-------------------Page "<< "1"<< "-------------------"<<endl;
                }
                else if ((linePrinted - 1) % 11 == 0)
                {
                    cout << "-------------------Page " << pagePrinted << "-------------------"<<endl;
                    pagePrinted++;
                }
                cout << linePrinted << ") " << temp->data << endl;
                temp = temp->next;
                linePrinted++;
            }
        }
    }

    void saveall()
    {
        node *temp = head;
        int linePrinted = 1;
        int pagePrinted = 2;
        string fname;
        cout << "Enter the file name : ";
        cin >> fname;
        fname += ".txt";
        fout.open(fname, ios_base::app);
        while (temp != NULL)
        {
            fout << temp->data;
            temp = temp->next;
            linePrinted++;
        }
        fout.flush();
        fout.close();
    }
};

int main()
{
    linked_list List;
    return 0;
}
