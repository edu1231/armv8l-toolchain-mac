/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QMACSTYLE_MAC_P_P_H
#define QMACSTYLE_MAC_P_P_H

#include <Carbon/Carbon.h>
#undef check

#include <QtWidgets/private/qtwidgetsglobal_p.h>
#include "qmacstyle_mac_p.h"
#include "qcommonstyle_p.h"
#include <private/qapplication_p.h>
#include <private/qcombobox_p.h>
#include <private/qpainter_p.h>
#include <private/qstylehelper_p.h>
#include <qapplication.h>
#include <qbitmap.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdialogbuttonbox.h>
#include <qdockwidget.h>
#include <qevent.h>
#include <qfocusframe.h>
#include <qformlayout.h>
#include <qgroupbox.h>
#include <qhash.h>
#include <qheaderview.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qmainwindow.h>
#include <qmap.h>
#include <qmenubar.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpixmapcache.h>
#include <qpointer.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qrubberband.h>
#include <qsizegrip.h>
#include <qspinbox.h>
#include <qsplitter.h>
#include <qstyleoption.h>
#include <qtextedit.h>
#include <qtextstream.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qtreeview.h>
#include <qtableview.h>
#include <qwizard.h>
#include <qdebug.h>
#include <qdatetimeedit.h>
#include <qmath.h>
#include <qpair.h>
#include <qvector.h>
#include <QtWidgets/qgraphicsproxywidget.h>
#include <QtWidgets/qgraphicsview.h>



//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

/*
    AHIG:
        Apple Human Interface Guidelines
        http://developer.apple.com/documentation/UserExperience/Conceptual/OSXHIGuidelines/

    Builder:
        Apple Interface Builder v. 3.1.1
*/

// this works as long as we have at most 16 different control types
#define CT1(c) CT2(c, c)
#define CT2(c1, c2) ((uint(c1) << 16) | uint(c2))

enum QAquaWidgetSize { QAquaSizeLarge = 0, QAquaSizeSmall = 1, QAquaSizeMini = 2,
                       QAquaSizeUnknown = -1 };

enum QCocoaWidgetKind {
    QCocoaArrowButton,  // Disclosure triangle, like in QTreeView
    QCocoaCheckBox,
    QCocoaComboBox,     // Editable QComboBox
    QCocoaPopupButton,  // Non-editable QComboBox
    QCocoaPullDownButton, // QPushButton with menu
    QCocoaPushButton,
    QCocoaRadioButton,
    QCocoaHorizontalSlider,
    QCocoaVerticalSlider
};

typedef QPair<QCocoaWidgetKind, QAquaWidgetSize> QCocoaWidget;

typedef void (^QCocoaDrawRectBlock)(NSRect, CGContextRef);

#define SIZE(large, small, mini) \
    (controlSize == QAquaSizeLarge ? (large) : controlSize == QAquaSizeSmall ? (small) : (mini))

// same as return SIZE(...) but optimized
#define return_SIZE(large, small, mini) \
    do { \
        static const int sizes[] = { (large), (small), (mini) }; \
        return sizes[controlSize]; \
    } while (0)

bool qt_mac_buttonIsRenderedFlat(const QPushButton *pushButton, const QStyleOptionButton *option);

class QMacStylePrivate : public QCommonStylePrivate
{
    Q_DECLARE_PUBLIC(QMacStyle)
public:
    QMacStylePrivate();
    ~QMacStylePrivate();

    // Ideally these wouldn't exist, but since they already exist we need some accessors.
    static const int PushButtonLeftOffset;
    static const int PushButtonTopOffset;
    static const int PushButtonRightOffset;
    static const int PushButtonBottomOffset;
    static const int MiniButtonH;
    static const int SmallButtonH;
    static const int BevelButtonW;
    static const int BevelButtonH;
    static const int PushButtonContentPadding;

    enum Animates { AquaPushButton, AquaProgressBar, AquaListViewItemOpen, AquaScrollBar };
    static ThemeDrawState getDrawState(QStyle::State flags);
    QAquaWidgetSize aquaSizeConstrain(const QStyleOption *option, const QWidget *widg,
                             QStyle::ContentsType ct = QStyle::CT_CustomBase,
                             QSize szHint=QSize(-1, -1), QSize *insz = 0) const;
    QAquaWidgetSize effectiveAquaSizeConstrain(const QStyleOption *option, const QWidget *widg,
                             QStyle::ContentsType ct = QStyle::CT_CustomBase,
                             QSize szHint=QSize(-1, -1), QSize *insz = 0) const;
    void getSliderInfo(QStyle::ComplexControl cc, const QStyleOptionSlider *slider,
                          HIThemeTrackDrawInfo *tdi, const QWidget *needToRemoveMe) const;
    inline int animateSpeed(Animates) const { return 33; }

    // Utility functions
    void drawColorlessButton(const HIRect &macRect, HIThemeButtonDrawInfo *bdi,
                             QPainter *p, const QStyleOption *opt) const;

    QSize pushButtonSizeFromContents(const QStyleOptionButton *btn) const;

    HIRect pushButtonContentBounds(const QStyleOptionButton *btn,
                                   const HIThemeButtonDrawInfo *bdi) const;

    void initComboboxBdi(const QStyleOptionComboBox *combo, HIThemeButtonDrawInfo *bdi,
                        const QWidget *widget, const ThemeDrawState &tds) const;

    static HIRect comboboxInnerBounds(const HIRect &outerBounds, int buttonKind);

    static QRect comboboxEditBounds(const QRect &outerBounds, const HIThemeButtonDrawInfo &bdi);

    static void drawCombobox(const HIRect &outerBounds, const HIThemeButtonDrawInfo &bdi, QPainter *p);
    static void drawTableHeader(const HIRect &outerBounds, bool drawTopBorder, bool drawLeftBorder,
                                     const HIThemeButtonDrawInfo &bdi, QPainter *p);
    bool contentFitsInPushButton(const QStyleOptionButton *btn, HIThemeButtonDrawInfo *bdi,
                                 ThemeButtonKind buttonKindToCheck) const;
    void initHIThemePushButton(const QStyleOptionButton *btn, const QWidget *widget,
                               const ThemeDrawState tds,
                               HIThemeButtonDrawInfo *bdi) const;
    QPixmap generateBackgroundPattern() const;

    void setAutoDefaultButton(QObject *button) const;

    NSView *cocoaControl(QCocoaWidget widget) const;

    void drawNSViewInRect(QCocoaWidget widget, NSView *view, const QRect &rect, QPainter *p, bool isQWidget = true, QCocoaDrawRectBlock drawRectBlock = nil) const;
    void resolveCurrentNSView(QWindow *window);

    void drawFocusRing(QPainter *p, const QRect &targetRect, int hMargin, int vMargin, qreal radius = 0) const;

public:
    mutable QPointer<QObject> pressedButton;
    mutable QPointer<QObject> defaultButton;
    mutable QPointer<QObject> autoDefaultButton;
    static  QVector<QPointer<QObject> > scrollBars;

    struct ButtonState {
        int frame;
        enum { ButtonDark, ButtonLight } dir;
    } buttonState;
    mutable QPointer<QFocusFrame> focusWidget;
    CFAbsoluteTime defaultButtonStart;
    bool mouseDown;
    void* receiver;
    void *nsscroller;
    void *indicatorBranchButtonCell;
    NSView *backingStoreNSView;
    QHash<QCocoaWidget, NSView *> cocoaControls;
};

QT_END_NAMESPACE

#endif // QMACSTYLE_MAC_P_P_H
