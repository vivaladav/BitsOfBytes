TEMPLATE = subdirs

SUBDIRS += \
    WidgetsLib \
    TesterPanelConcat \
    ExampleApp

lib.subdirs = WidgetsLib
tests.subdirs = TesterPanelConcat
app.subdirs = ExampleApp

app.depends = lib
tests.depends = lib
