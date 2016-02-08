using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Service;
using Domain;

namespace ContactsApp
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public Services services;
        public MainWindow()
        {
            InitializeComponent();

            services = new Services();
            LoadData(services.GetGroups());
        }


        public void LoadData(List<Group> groups)
        {
            listView.Items.Clear();

            foreach (TreeViewItem item in treeView.Items)
            {
                item.UnregisterName(item.Header.ToString());
            }
            treeView.Items.Clear();

            foreach (Group group in groups)
            {
                TreeViewItem treeViewItem = new TreeViewItem() { Header = group.Name, Tag = group };
                treeView.Items.Add(treeViewItem);
                treeViewItem.RegisterName(group.Name, treeViewItem);

                var persons = group.Persons;

                foreach (Person person in persons)
                {
                    ListViewItem listViewItem = new ListViewItem() { Content = person, Tag = person };
                    listView.Items.Add(listViewItem);

                    TreeViewItem i = treeView.FindName(group.Name) as TreeViewItem;
                    TreeViewItem treeViewSubItem = new TreeViewItem() { Header = person.Name, Tag = person };
                    i.Items.Add(treeViewSubItem);
                }

                treeViewItem.IsExpanded = true;
            }
        }

        private void MenuItem_Click_LoadContacts(object sender, RoutedEventArgs e)
        {
            services.LoadContacts();
        }

        private void MenuItem_Click_SaveContacts(object sender, RoutedEventArgs e)
        {
            services.SaveContacts();
        }

        private void MenuItem_Click_About(object sender, RoutedEventArgs e)
        {
            AboutBox aboutBox = new AboutBox();
            aboutBox.ShowDialog();
        }

        private void MenuItem_Click_ContactsNew(object sender, RoutedEventArgs e)
        {
            Person newPerson = new Person();
            PersonWindow personWindow = new PersonWindow(ref services, ref newPerson, EditMode.New);
            personWindow.ShowDialog();
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_ContactsInfo(object sender, RoutedEventArgs e)
        {
            ListViewItem selectedListViewItem = listView.SelectedItem as ListViewItem;
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Person selectedPerson = new Person();

            if (selectedListViewItem == null && selectedTreeViewItem == null)
            {
                MessageBox.Show("Nothing is Selected");
                return;
            }
            else if (selectedListViewItem != null && selectedTreeViewItem == null)
            {
                selectedPerson = selectedListViewItem.Tag as Person;
            }
            else if (selectedListViewItem == null && selectedTreeViewItem != null)
            {
                selectedPerson = selectedTreeViewItem.Tag as Person;
            }

            PersonWindow personWindow = new PersonWindow(ref services, ref selectedPerson, EditMode.Info);
            personWindow.ShowDialog();
        }

        private void MenuItem_Click_ContactsUpdate(object sender, RoutedEventArgs e)
        {
            ListViewItem selectedListViewItem = listView.SelectedItem as ListViewItem;
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Person selectedPerson = new Person();

            if (selectedListViewItem == null && selectedTreeViewItem == null)
            {
                MessageBox.Show("Nothing is Selected");
                return;
            }
            else if (selectedListViewItem != null && selectedTreeViewItem == null)
            {
                selectedPerson = selectedListViewItem.Tag as Person;
            }
            else if (selectedListViewItem == null && selectedTreeViewItem != null)
            {
                selectedPerson = selectedTreeViewItem.Tag as Person;
            }

            PersonWindow personWindow = new PersonWindow(ref services, ref selectedPerson, EditMode.Update);
            personWindow.ShowDialog();
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_ContactsDelete(object sender, RoutedEventArgs e)
        {
            ListViewItem selectedListViewItem = listView.SelectedItem as ListViewItem;
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Person selectedPerson = new Person();

            if (selectedListViewItem == null && selectedTreeViewItem == null)
            {
                MessageBox.Show("Nothing is Selected");
                return;
            }
            else if (selectedListViewItem != null && selectedTreeViewItem == null)
            {
                selectedPerson = selectedListViewItem.Tag as Person;
            }
            else if (selectedListViewItem == null && selectedTreeViewItem != null)
            {
                selectedPerson = selectedTreeViewItem.Tag as Person;
            }

            services.DeletePerson(selectedPerson);
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_GroupsNew(object sender, RoutedEventArgs e)
        {
            Group newGroup = new Group();
            GroupWindow groupWindow = new GroupWindow(ref services, ref newGroup, EditMode.New);
            groupWindow.ShowDialog();
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_GroupsInfo(object sender, RoutedEventArgs e)
        {
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Group group = selectedTreeViewItem.Tag as Group;
            GroupWindow groupWindow = new GroupWindow(ref services, ref group, EditMode.Info);
            groupWindow.ShowDialog();
            selectedTreeViewItem.IsExpanded = true;
        }

        private void MenuItem_Click_GroupsUpdate(object sender, RoutedEventArgs e)
        {
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Group group = selectedTreeViewItem.Tag as Group;
            GroupWindow groupWindow = new GroupWindow(ref services, ref group, EditMode.Update);
            groupWindow.ShowDialog();
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_GroupsDelete(object sender, RoutedEventArgs e)
        {
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Group group = selectedTreeViewItem.Tag as Group;
            services.DeleteGroup(group);
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_ContactsMoveToGroup(object sender, RoutedEventArgs e)
        {
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Person selectedPerson = selectedTreeViewItem.Tag as Person;
            TreeViewItem parentTreeViewItem = selectedTreeViewItem.Parent as TreeViewItem;
            Group curGroup = parentTreeViewItem.Tag as Group;
            ModifyGroupWindow modifyGroupWindow = new ModifyGroupWindow(ref services, ref curGroup, ref selectedPerson, ModifyGroupMode.Move);
            modifyGroupWindow.ShowDialog();
            LoadData(services.GetGroups());
        }

        private void MenuItem_Click_ContactsAddToGroup(object sender, RoutedEventArgs e)
        {
            TreeViewItem selectedTreeViewItem = treeView.SelectedItem as TreeViewItem;
            Person selectedPerson = selectedTreeViewItem.Tag as Person;
            TreeViewItem parentTreeViewItem = selectedTreeViewItem.Parent as TreeViewItem;
            Group curGroup = parentTreeViewItem.Tag as Group;
            ModifyGroupWindow modifyGroupWindow = new ModifyGroupWindow(ref services, ref curGroup, ref selectedPerson, ModifyGroupMode.Add);
            modifyGroupWindow.ShowDialog();
            LoadData(services.GetGroups());
        }

        private void TreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            TreeViewItem selectedItem = treeView.SelectedItem as TreeViewItem;

            if (selectedItem != null)
            {
                object itemTag = selectedItem.Tag;
                Type itemType = itemTag.GetType();

                if (itemType.ToString() == "Domain.Person")
                {
                    treeView.ContextMenu = treeView.Resources["PersonContext"] as ContextMenu;
                }
                else if (itemType.ToString() == "Domain.Group")
                {
                    treeView.ContextMenu = treeView.Resources["GroupContext"] as ContextMenu;
                }
            }
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (textBox.Text.Length == 0)
            {
                LoadData(services.GetGroups());
            }
            else
            {
                TabItem tabItem = tabControl.SelectedValue as TabItem;

                if (tabItem.Name == "Contacts")
                {
                    string condition = textBox.Text;
                    List<Group> res = services.SearchPerson(condition);
                    LoadData(res);
                }
                else if (tabItem.Name == "Groups")
                {
                    string condition = textBox.Text;
                    List<Group> res = services.SearchGroup(condition);
                    LoadData(res);
                }
            }
        }
    }
}
