/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center, 
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without 
even the implied warranty of MERCHANTABILITY or FITNESS FOR 
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "TestApplicationWorkbenchWindowAdvisor.h"
//#include "QmitkActionBarAdvisor.h"


#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QStatusBar>
#include <QToolBar>
#include <QProgressBar>
#include <QLabel>
#include <QTabBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QComboBox>
//
//#include <berryPlatform.h>
#include <berryPlatformUI.h>
//#include <berryIWorkbenchWindow.h>
//#include <berryIPreferencesService.h>
#include <berryIViewRegistry.h>
#include <internal/berryQtControlWidget.h>
//#include <berryQtShell.h>
//#include "D:/Plattformprojekt/MITK/BlueBerry/Bundles/org.blueberry.ui.qt/src/internal/berryQtShell.h"
//
//#include <internal/berryQtShowViewAction.h>
//
//#include <QmitkFileOpenAction.h>
//#include <QmitkFileExitAction.h>
//#include <QmitkStatusBar.h>
//#include <QmitkProgressBar.h>
//#include <QmitkMemoryUsageIndicatorView.h>
//#include <QmitkDefaultDropTargetListener.h>
//

//TestApplicationWorkbenchWindowAdvisor::TestApplicationWorkbenchWindowAdvisor(berry::IWorkbenchWindowConfigurer::Pointer configurer)
//: berry::WorkbenchWindowAdvisor(configurer)
//, dropTargetListener(new QmitkDefaultDropTargetListener)
//{
//}

TestApplicationWorkbenchWindowAdvisor::TestApplicationWorkbenchWindowAdvisor(berry::IWorkbenchWindowConfigurer::Pointer configurer)
: berry::WorkbenchWindowAdvisor(configurer)
{
}

berry::ActionBarAdvisor::Pointer
TestApplicationWorkbenchWindowAdvisor::CreateActionBarAdvisor(
  berry::IActionBarConfigurer::Pointer configurer)
{
  berry::ActionBarAdvisor::Pointer actionBarAdvisor(new berry::ActionBarAdvisor(configurer));
  return actionBarAdvisor;
}

void TestApplicationWorkbenchWindowAdvisor::PostWindowCreate()
{
  // very bad hack...
  berry::IWorkbenchWindow::Pointer window = this->GetWindowConfigurer()->GetWindow();
  QMainWindow* mainWindow = static_cast<QMainWindow*>(window->GetShell()->GetControl());

  QMenuBar* menuBar = mainWindow->menuBar();

  QMenu* fileMenu = menuBar->addMenu("File");
  fileMenu->addAction("Open Nothing");

  //fileMenu->addAction(new QmitkFileOpenAction(window));
  //fileMenu->addSeparator();
  //fileMenu->addAction(new QmitkFileExitAction(window));

  berry::IViewRegistry* viewRegistry = berry::PlatformUI::GetWorkbench()->GetViewRegistry();
  const std::vector<berry::IViewDescriptor::Pointer>& viewDescriptors = viewRegistry->GetViews();

  QMenu* viewMenu = menuBar->addMenu("Show View");
  viewMenu->addAction("Show Nothing New");

  //// sort elements (converting vector to map...)
  //std::vector<berry::IViewDescriptor::Pointer>::const_iterator iter;
  //std::map<std::string, berry::IViewDescriptor::Pointer> VDMap;

  //for (iter = viewDescriptors.begin(); iter != viewDescriptors.end(); ++iter)
  //{
  //  if ((*iter)->GetId() == "org.blueberry.ui.internal.introview")
  //    continue;
  //  std::pair<std::string, berry::IViewDescriptor::Pointer> p((*iter)->GetLabel(), (*iter)); 
  //  VDMap.insert(p);
  //}

  QToolBar* qToolbar = new QToolBar;
  //
  //std::map<std::string, berry::IViewDescriptor::Pointer>::const_iterator MapIter;
  //for (MapIter = VDMap.begin(); MapIter != VDMap.end(); ++MapIter)
  //{
  //  berry::QtShowViewAction* viewAction = new berry::QtShowViewAction(window, (*MapIter).second);
  //  //m_ViewActions.push_back(viewAction);
  //  viewMenu->addAction(viewAction);
  //  qToolbar->addAction(viewAction);
  //}
  
  mainWindow->addToolBar(qToolbar);

  QStatusBar* qStatusBar = new QStatusBar();
  QLabel* title = new QLabel("Status Bar");

  title->setAlignment( Qt::AlignLeft );
  title->setText("Test Application Status Bar");
  title->setToolTip("This is the Status Bar");
    
  qStatusBar->addWidget(title);
  //qStatusBar->addPermanentWidget(title);

  mainWindow->setStatusBar(qStatusBar);

  QProgressBar *progBar = new QProgressBar();
  qStatusBar->addPermanentWidget(progBar, 0);
  //progBar->hide();

  //creating a QmitkStatusBar for Output on the QStatusBar and connecting it with the MainStatusBar
  //QmitkStatusBar *statusBar = new QmitkStatusBar(qStatusBar);
  //disabling the SizeGrip in the lower right corner
  //statusBar->SetSizeGripEnabled(false);

  /*QmitkProgressBar *progBar = new QmitkProgressBar();
  qStatusBar->addPermanentWidget(progBar, 0);
  progBar->hide();*/



  /*QmitkMemoryUsageIndicatorView* memoryIndicator = new QmitkMemoryUsageIndicatorView();
  qStatusBar->addPermanentWidget(memoryIndicator, 0);*/
}

void TestApplicationWorkbenchWindowAdvisor::PreWindowOpen()
{
  berry::IWorkbenchWindowConfigurer::Pointer configurer = this->GetWindowConfigurer();
  configurer->SetShowCoolBar(true);
  configurer->SetShowMenuBar(true);
  configurer->SetShowPerspectiveBar(true);
  configurer->SetShowStatusLine(true);
  configurer->SetTitle("TestApplication");

  //this->GetWindowConfigurer()->AddEditorAreaTransfer(QStringList("text/uri-list"));
  //this->GetWindowConfigurer()->ConfigureEditorAreaDropListener(dropTargetListener);
}

void TestApplicationWorkbenchWindowAdvisor::CreateWindowContents(berry::Shell::Pointer shell)
{
  /*berry::QtShell* qtShell = dynamic_cast<berry::QtShell*>(&(*shell));
  this->GetWindowConfigurer()->CreatePageComposite(static_cast<void*>(qtShell->GetWidget()));*/

  /*berry::IWorkbenchWindow::Pointer window = this->GetWindowConfigurer()->GetWindow();
  QMainWindow* mainWindow = static_cast<QMainWindow*>(window->GetShell()->GetControl());*/

  QMainWindow* mainWindow = static_cast<QMainWindow*>(shell->GetControl());
  mainWindow->setVisible(true);
  //QVBoxLayout* mainWindowLayout = new QVBoxLayout(mainWindow);

  QWidget* CentralWidget = new QWidget(mainWindow);
  CentralWidget->setVisible(true);
  //QWidget* CentralWidget = new berry::QtControlWidget(mainWindow, shell.GetPointer());
  QWidget* PageComposite = new QWidget(CentralWidget);
  PageComposite->setVisible(true);
  //QWidget* PageComposite = new berry::QtControlWidget(CentralWidget, shell.GetPointer());
  QTabBar* PerspectivesTabBar = new QTabBar(CentralWidget);
  PerspectivesTabBar->addTab("Perspective 1");
  PerspectivesTabBar->addTab("Perspective 2");
  PerspectivesTabBar->setVisible(true);
  QVBoxLayout* CentralWidgetLayout = new QVBoxLayout(CentralWidget);
  CentralWidgetLayout->addWidget(PerspectivesTabBar);
  CentralWidgetLayout->addWidget(PageComposite);
  CentralWidget->setLayout(CentralWidgetLayout);
  //CentralWidget->resize(mainWindow->size());
  //QSize Size = CentralWidget->size();
  QHBoxLayout* PageCompositeLayout = new QHBoxLayout(PageComposite);
  PageComposite->setLayout(PageCompositeLayout);
  //PageComposite->resize(mainWindow->size());
  //Size = PageComposite->size();

  mainWindow->setCentralWidget(CentralWidget);
  PageCompositeLayout->activate();
  PageCompositeLayout->update();
  CentralWidgetLayout->activate();
  CentralWidgetLayout->update();
  this->GetWindowConfigurer()->CreatePageComposite(static_cast<void*>(PageComposite));

  

  //QComboBox* ComboBox = new QComboBox(mainWindow);

  //QLabel* entry = new QLabel("Status Bar");
  ////entry->setAlignment( Qt::AlignLeft );
  //entry->setText("Test Entry");
  //entry->setToolTip("This is a Test Entry");

  /*ComboBox->addItem("TestEntry");
  ComboBox->move(200,0);
  ComboBox->setVisible(true);*/
  /*berry::IWorkbenchWindowConfigurer::Pointer configurer = this->GetWindowConfigurer();
  configurer->CreatePageComposite(static_cast<void*>(&(*shell)));*/
  
  //this->GetWindowConfigurer()->CreatePageComposite(static_cast<void*>(shell*));
}