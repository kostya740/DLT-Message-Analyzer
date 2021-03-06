#ifndef CCONSOLEINPUTPROCESSOR_HPP
#define CCONSOLEINPUTPROCESSOR_HPP

#include "map"
#include "string"
#include "functional"
#include "deque"

#include <QLineEdit>

class CConsoleInputProcessor : public QObject
{
    Q_OBJECT

public:

    typedef QString tScenarioTag;
    typedef QString tParamName;
    typedef QString tParamValue;

    typedef std::map<tParamName, tParamValue> tParamMap;

    typedef std::function<void(const tParamMap&)> tScenarioHandler;

    struct tScenarioData
    {
        tScenarioData() = default;
        tScenarioData( const tScenarioHandler& scenarioHandler_,
                       const QString& comment_ );
        tScenarioHandler scenarioHandler;
        QString comment;
    };

    typedef std::map<tScenarioTag, tScenarioData> tScenariosMap;

    CConsoleInputProcessor( QLineEdit* pTargetLineEdit );
    virtual ~CConsoleInputProcessor();

protected:
    bool eventFilter(QObject* pObj, QEvent* pEvent) override;

private:

    QLineEdit* mpTargetLineEdit;
    tScenariosMap mScenariosMap;
    std::deque<QString> mHistory;
    int mCurrentHistoryItem;

    enum eHistoryBorderStatus
    {
        Reached_Both = 0,
        Reached_First,
        Reached_Last,
        Not_Near_Border
    };

    eHistoryBorderStatus mbBorderReached;
};

#endif // CCONSOLEINPUTPROCESSOR_HPP
