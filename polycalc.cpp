#include <iostream>
#include <cmath>
using namespace std;

class Node
{
public:
    int coeff;
    int exp;
    Node *next;

    Node(int c, int e)
    {
        coeff = c;
        exp = e;
        next = NULL;
    }
};

class Polynomial
{
    Node *head;

public:
    Polynomial()
    {
        head = NULL;
    }

    Node *getHead()
    {
        return head;
    }

    // Insert term in descending order of exponent
    void insertTerm(int c, int e)
    {
        if (c == 0)
            return;

        Node *newNode = new Node(c, e);

        if (head == NULL || head->exp < e)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *temp = head;
        Node *prev = NULL;

        while (temp != NULL && temp->exp > e)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL && temp->exp == e)
        {
            temp->coeff += c;
            delete newNode;

            if (temp->coeff == 0)
            {
                if (prev == NULL)
                    head = temp->next;
                else
                    prev->next = temp->next;

                delete temp;
            }
            return;
        }

        newNode->next = temp;
        prev->next = newNode;
    }

    // Create polynomial
    void create()
    {
        int n, c, e;

        cout << "Enter number of terms: ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "Coefficient: ";
            cin >> c;

            cout << "Exponent: ";
            cin >> e;

            insertTerm(c, e);
        }
    }

    // Display polynomial
    void display()
    {
        if (head == NULL)
        {
            cout << "0\n";
            return;
        }

        Node *temp = head;

        while (temp)
        {
            if (temp->coeff > 0 && temp != head)
                cout << "+";

            if (temp->exp == 0)
                cout << temp->coeff;
            else if (temp->exp == 1)
                cout << temp->coeff << "x";
            else
                cout << temp->coeff << "x^" << temp->exp;

            temp = temp->next;
        }
        cout << endl;
    }

    // Addition
    Polynomial add(Polynomial p2)
    {
        Polynomial result;

        Node *p = head;
        Node *q = p2.head;

        while (p && q)
        {
            if (p->exp == q->exp)
            {
                result.insertTerm(p->coeff + q->coeff, p->exp);
                p = p->next;
                q = q->next;
            }
            else if (p->exp > q->exp)
            {
                result.insertTerm(p->coeff, p->exp);
                p = p->next;
            }
            else
            {
                result.insertTerm(q->coeff, q->exp);
                q = q->next;
            }
        }

        while (p)
        {
            result.insertTerm(p->coeff, p->exp);
            p = p->next;
        }

        while (q)
        {
            result.insertTerm(q->coeff, q->exp);
            q = q->next;
        }

        return result;
    }

    // Subtraction
    Polynomial subtract(Polynomial p2)
    {
        Polynomial result;

        Node *p = head;
        Node *q = p2.head;

        while (p && q)
        {
            if (p->exp == q->exp)
            {
                result.insertTerm(p->coeff - q->coeff, p->exp);
                p = p->next;
                q = q->next;
            }
            else if (p->exp > q->exp)
            {
                result.insertTerm(p->coeff, p->exp);
                p = p->next;
            }
            else
            {
                result.insertTerm(-q->coeff, q->exp);
                q = q->next;
            }
        }

        while (p)
        {
            result.insertTerm(p->coeff, p->exp);
            p = p->next;
        }

        while (q)
        {
            result.insertTerm(-q->coeff, q->exp);
            q = q->next;
        }

        return result;
    }

    // Multiplication
    Polynomial multiply(Polynomial p2)
    {
        Polynomial result;

        for (Node *p = head; p != NULL; p = p->next)
        {
            for (Node *q = p2.head; q != NULL; q = q->next)
            {
                result.insertTerm(
                    p->coeff * q->coeff,
                    p->exp + q->exp);
            }
        }

        return result;
    }

    // Evaluation
    double evaluate(double x)
    {
        double ans = 0;
        Node *temp = head;

        while (temp)
        {
            ans += temp->coeff * pow(x, temp->exp);
            temp = temp->next;
        }

        return ans;
    }

    // Division by (x-a)
    void divideByLinear(int a)
    {
        int degree = head->exp;
        int coeffs[20] = {0};

        Node *temp = head;

        while (temp)
        {
            coeffs[temp->exp] = temp->coeff;
            temp = temp->next;
        }

        int b[20];

        b[degree] = coeffs[degree];

        for (int i = degree - 1; i >= 0; i--)
        {
            b[i] = coeffs[i] + a * b[i + 1];
        }

        cout << "Quotient: ";

        for (int i = degree; i >= 1; i--)
        {
            if (b[i] == 0)
                continue;

            cout << b[i] << "x^" << i - 1;

            if (i != 1)
                cout << " + ";
        }

        cout << endl;
        cout << "Remainder = " << b[0] << endl;
    }

    // Factorization up to degree 4
    void factorize()
    {
        int degree = head->exp;

        if (degree > 4)
        {
            cout << "Factorization supported only up to degree 4.\n";
            return;
        }

        cout << "Possible integer roots:\n";

        for (int i = -20; i <= 20; i++)
        {
            if (i == 0)
                continue;

            if (evaluate(i) == 0)
                cout << "(x - " << i << ") is a factor.\n";
        }
    }
};

int main()
{
    Polynomial p1, p2, result;
    int choice;

    do
    {
        cout << "\n====== POLYNOMIAL CALCULATOR ======\n";
        cout << "1. Create Polynomial 1\n";
        cout << "2. Create Polynomial 2\n";
        cout << "3. Display\n";
        cout << "4. Addition\n";
        cout << "5. Subtraction\n";
        cout << "6. Multiplication\n";
        cout << "7. Division by (x-a)\n";
        cout << "8. Factorization\n";
        cout << "9. Evaluation\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            p1.create();
            break;

        case 2:
            p2.create();
            break;

        case 3:
            cout << "Polynomial 1: ";
            p1.display();
            cout << "Polynomial 2: ";
            p2.display();
            break;

        case 4:
            result = p1.add(p2);
            cout << "Addition = ";
            result.display();
            break;

        case 5:
            result = p1.subtract(p2);
            cout << "Subtraction = ";
            result.display();
            break;

        case 6:
            result = p1.multiply(p2);
            cout << "Multiplication = ";
            result.display();
            break;

        case 7:
        {
            int a;
            cout << "Enter a for divisor (x-a): ";
            cin >> a;
            p1.divideByLinear(a);
            break;
        }

        case 8:
            p1.factorize();
            break;

        case 9:
        {
            double x;
            cout << "Enter value of x: ";
            cin >> x;
            cout << "P(x) = " << p1.evaluate(x) << endl;
            break;
        }

        case 10:
            cout << "Program Ended.\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 10);

    return 0;
}