#include <QTest/QTest>

class TestValueControl : public QObject
{
    Q_OBJECT

    private slots:
    void ValueControl();
};

void TestValueControl::ValueControl()
{

}

QTEST_MAIN(TestQString)
#include "ValueControlTest.moc"
