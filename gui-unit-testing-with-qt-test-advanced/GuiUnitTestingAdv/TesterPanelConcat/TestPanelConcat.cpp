#include "PanelConcat.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalSpy>
#include <QString>
#include <QtTest>

const QString STR1("blog.");
const QString STR2("davidecoppola.com");
const QString STR_RES(STR1 + STR2);

class TestPanelConcat : public QObject
{
	Q_OBJECT

private slots:
	void init();

	void TestFocusOrder();
	void TestFocusUsage();

	void TestSignals();

private:
	PanelConcat mPanel;
};

void TestPanelConcat::init()
{
	mPanel.CancelData();
}

void TestPanelConcat::TestFocusOrder()
{
	// enables focus and widget events
	QApplication::setActiveWindow(&mPanel);

	// set initial focus
	mPanel.mInputA->setFocus();
	QVERIFY2(mPanel.mInputA->hasFocus(), "Input A didn't get focus");

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mInputB->hasFocus(), "Input B didn't get focus");

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonConcat->hasFocus(), "Button CONCAT didn't get focus");

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonCancel->hasFocus(), "Button CANCEL didn't get focus");
}

void TestPanelConcat::TestFocusUsage()
{
	// enables focus and widget events
	QApplication::setActiveWindow(&mPanel);

	// set initial focus
	mPanel.mInputA->setFocus();
	QVERIFY2(mPanel.mInputA->hasFocus(), "Input A doesn't have focus");

	// write STR1
	QTest::keyClicks(QApplication::focusWidget(), STR1);

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mInputB->hasFocus(), "Input B doesn't have focus");

	// write STR2
	QTest::keyClicks(QApplication::focusWidget(), STR2);

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonConcat->hasFocus(), "Button CONCAT doesn't have focus");

	// press button CONCAT using space
	QTest::keyClick(QApplication::focusWidget(), Qt::Key_Space);
	QCOMPARE(mPanel.mLabelRes->text(), STR_RES);

	// move focus to next widget
	QTest::keyClick(&mPanel, Qt::Key_Tab);
	QVERIFY2(mPanel.mButtonCancel->hasFocus(), "Button CANCEL doesn't have focus");

	// press button CANCEL using space
	QTest::keyClick(QApplication::focusWidget(), Qt::Key_Space);
	QVERIFY2(mPanel.mInputA->text().isEmpty(), "Cancel didn't work on input A");
	QVERIFY2(mPanel.mInputB->text().isEmpty(), "Cancel didn't work on input B");
	QVERIFY2(mPanel.mLabelRes->text().isEmpty(), "Cancel didn't work on res label");
}

void TestPanelConcat::TestSignals()
{
	// set input
	mPanel.mInputA->setText(STR1);
	mPanel.mInputB->setText(STR2);

	// create spy objects
	QSignalSpy spy1(&mPanel, &PanelConcat::DataAvailable);
	QSignalSpy spy2(&mPanel, &PanelConcat::DataCleared);

	// click button CONCAT
	QTest::mouseClick(mPanel.mButtonConcat, Qt::LeftButton);

	QCOMPARE(spy1.count(), 1);
	QCOMPARE(spy2.count(), 0);

	QList<QVariant> args = spy1.takeFirst();
	QCOMPARE(args.at(0).toString(), STR_RES);

	// click button CANCEL
	QTest::mouseClick(mPanel.mButtonCancel, Qt::LeftButton);

	QCOMPARE(spy1.count(), 0);
	QCOMPARE(spy2.count(), 1);

	args = spy2.takeFirst();
	QVERIFY2(args.empty(), "DataCleared signal has parameters now?!?");
}

QTEST_MAIN(TestPanelConcat)

#include "TestPanelConcat.moc"
