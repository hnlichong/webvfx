// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBVFX_WEB_PAGE_H_
#define WEBVFX_WEB_PAGE_H_

#include <string>
#include <QWebPage>
#include "webvfx/image.h"
#include "webvfx/rendering_context.h"
#include "webvfx/effects.h"

class QEventLoop;
class QImage;
class QSize;
class QWebFrame;

namespace WebVFX
{

class Parameters;

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    WebPage(QObject* parent, QSize size, Parameters* parameters);
    ~WebPage();

    // Load URL synchronously, return success
    bool loadSync(const QUrl& url);
    const Effects::ImageTypeMap& getImageTypeMap() { return imageTypeMap; };
    Image render(double time);
    Image getImage(const QString& name, const QSize& size) { return renderingContext->getImage(name, size); }

private slots:
    void injectRenderingContext();
    bool shouldInterruptJavaScript();
    void webPageLoadFinished(bool result);
    void renderingContextLoadFinished(bool result, const QVariantMap& imageTypeMap);

protected:
    void javaScriptAlert(QWebFrame* originatingFrame, const QString& msg);
    void javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID);
    bool acceptNavigationRequest(QWebFrame* frame, const QNetworkRequest& request, NavigationType type);

private:
    enum LoadStatus { LoadNotFinished, LoadFailed, LoadSucceeded };
    LoadStatus pageLoadFinished;
    LoadStatus scriptLoadFinished;
    RenderingContext* renderingContext;
    QEventLoop* syncLoop;
    QImage* renderImage;
    Effects::ImageTypeMap imageTypeMap;
};

}

#endif
