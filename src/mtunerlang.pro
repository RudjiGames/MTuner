#-------------------------------------------------
#
# Dummy .pro file used for translations
#
#-------------------------------------------------

QT += core gui network

INCLUDEPATH += .

TARGET = MTuner
TEMPLATE = app

SOURCES +=  about.cpp               \
            bigtable.cpp            \
            binloaderview.cpp       \
            capturecontext.cpp      \
            centralwidget.cpp       \
            external_editor.cpp     \
            gcc.cpp                 \
            graph.cpp               \
            graphcurve.cpp          \
            graphgrid.cpp           \
            graphmarkers.cpp        \
            graphselect.cpp         \
            graphwidget.cpp         \
            grouplistwidget.cpp     \
            heapswidget.cpp         \
            highlighter.cpp         \
            histogram.cpp           \
            histogramview.cpp       \
            histogramwidget.cpp     \
            hotspots.cpp            \
            langmanager.cpp         \
            mtuner.cpp              \
            mtunermain.cpp          \
            MTuner_pch.cpp          \
            new_version.cpp         \
            operationsearch.cpp     \
            operationslist.cpp      \
            projectsmanager.cpp     \
            protection.cpp          \
            simplecrypt.cpp         \
            sourceview.cpp          \
            splash_nag.cpp          \
            splash_nag_ivory.cpp    \
            stackandsource.cpp      \
            stacktrace.cpp          \
            stacktreewidget.cpp     \
            startpage.cpp           \
            stats.cpp               \
            symbolstore.cpp         \
            tagtreewidget.cpp       \
            treemap.cpp             \
            treemapview.cpp         \
            welcome.cpp


HEADERS  += about.h                 \
            bigtable.h              \
            bigtabletablewidget.h   \
            binloaderview.h         \
            buildversion.h          \
            capturecontext.h        \
            centralwidget.h         \
            cmdline.h               \
            external_editor.h       \
            gcc.h                   \
            graph.h                 \
            graphcurve.h            \
            graphgrid.h             \
            graphmarkers.h          \
            graphselect.h           \
            graphwidget.h           \
            grouplistwidget.h       \
            heapswidget.h           \
            highlighter.h           \
            histogram.h             \
            histogramview.h         \
            histogramwidget.h       \
            hotspots.h              \
            langmanager.h           \
            mtuner.h                \
            MTuner_pch.h            \
            new_version.h           \
            operationsearch.h       \
            operationslist.h        \
            projectsmanager.h       \
            protection.h            \
            simplecrypt.h           \
            sourceview.h            \
            splash_nag.h            \
            splash_nag_ivory.h      \
            stackandsource.h        \
            stacktrace.h            \
            stacktreewidget.h       \
            startpage.h             \
            stats.h                 \
            symbolstore.h           \
            tagtreewidget.h         \
            treemap.h               \
            treemapview.h           \
            utility.h               \
            version.h               \
            welcome.h
			

FORMS    += about.ui                \
            bigtable.ui             \
            binloaderview.ui        \
            centralwidget.ui        \
            external_editor.ui      \
            gcc.ui                  \
            graph.ui                \
            grouplist.ui            \
            heapswidget.ui          \
            histogram.ui            \
            hotspot.ui              \
            mtuner.ui               \
            new_version.ui          \
            operationsearch.ui      \
            operationslist.ui       \
            progressbar.ui          \
            projectsmanager.ui      \
            splash_nag.ui           \
            splash_nag_ivory.ui     \
            stackandsource.ui       \
            stacktrace.ui           \
            stacktree.ui            \
            startpage.ui            \
            stats.ui                \
            symbolstore.ui          \
            tagtree.ui              \
            treemap.ui              \
            welcome.ui
			

RESOURCES += mtuner.qrc

TRANSLATIONS += mtuner_en.ts \
				mtuner_rs.ts \
				mtuner_it.ts \
				mtuner_de.ts

