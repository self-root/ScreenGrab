#ifndef RESULTTEXTVIEWCONTROLLER_H
#define RESULTTEXTVIEWCONTROLLER_H

#include <QObject>
#include <QVector>
#include "ScreenGrabCore_global.h"

struct MatchSequence
{
    int start;
    int end;
};

class SCREENGRABCORE_EXPORT ResultTextViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int selectionStart READ selectionStart CONSTANT)
    Q_PROPERTY(int selectionEnd READ selectionEnd CONSTANT)
public:
    explicit ResultTextViewController(QObject *parent = nullptr);

    int selectionStart() const;
    void setSelectTionStart(int newSelectTionStart);

    int selectionEnd() const;
    void setSelectionEnd(int newSelectionEnd);

public slots:
    void find(const QString &pattern, const QString &str);

    /**
     * @brief next Select the next word that match the pattern
     */
    void next();

private:
    int mSelectTionStart;
    int mSelectionEnd;
    int currentSelected = 0;

    QVector<MatchSequence> sequences;

signals:
    void selectionReady();

};

#endif // RESULTTEXTVIEWCONTROLLER_H
