#include "resulttextviewcontroller.h"

ResultTextViewController::ResultTextViewController(QObject *parent)
    : QObject{parent}
{

}

int ResultTextViewController::selectionStart() const
{
    return mSelectTionStart;
}

void ResultTextViewController::setSelectTionStart(int newSelectTionStart)
{
    mSelectTionStart = newSelectTionStart;
}

int ResultTextViewController::selectionEnd() const
{
    return mSelectionEnd;
}

void ResultTextViewController::setSelectionEnd(int newSelectionEnd)
{
    mSelectionEnd = newSelectionEnd;
}

void ResultTextViewController::find(const QString &pattern, const QString &str)
{
    sequences.clear();
    currentSelected = 0;
    int i = 0;
    for(int index = str.indexOf(pattern, i, Qt::CaseInsensitive);
        index >= 0; index = str.indexOf(pattern, i, Qt::CaseInsensitive))
    {
        MatchSequence s;
        s.start = index;
        s.end = index + pattern.length();
        i = s.end + 1;
        sequences.push_back(s);
    }

    if (!sequences.empty())
    {
        setSelectTionStart(sequences.first().start);
        setSelectionEnd(sequences.first().end);
        emit selectionReady();
        return;
    }
    setSelectTionStart(0);
    setSelectionEnd(0);
    emit selectionReady();
}

void ResultTextViewController::next()
{
    if (sequences.empty())
        return;
    if (currentSelected < sequences.size()-1)
    {
        currentSelected++; //The first word has already been selected
        setSelectTionStart(sequences.at(currentSelected).start);
        setSelectionEnd(sequences.at(currentSelected).end);
        emit selectionReady();
    }
    // Every word in the sequence has been selected, go back to the first word
    else {
        currentSelected = 0;
        setSelectTionStart(sequences.at(currentSelected).start);
        setSelectionEnd(sequences.at(currentSelected).end);
        emit selectionReady();
    }
}
