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
using System.Windows.Shapes;
using Domain;
using Service;

namespace ContactsApp
{
    /// <summary>
    /// ModifyGroupWindow.xaml 的交互逻辑
    /// </summary>
    public partial class ModifyGroupWindow : Window
    {
        Services services;
        Group curGroup;
        Person person;
        ModifyGroupMode mode;
        public ModifyGroupWindow(ref Services services, ref Group curGroup, ref Person person, ModifyGroupMode mode)
        {
            InitializeComponent();
            this.services = services;
            this.curGroup = curGroup;
            this.person = person;
            this.mode = mode;

            InitializeUI();
        }
        public void InitializeUI()
        {
            foreach (Group group in services.GetGroups())
            {
                if (group.Id != curGroup.Id)
                {
                    ComboBoxItem item = new ComboBoxItem() { Name = group.Name, Content = group.Name, Tag = group };
                    comboBox.Items.Add(item);
                }
            }
        }

        private void OK_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (mode == ModifyGroupMode.Move)
            {
                ComboBoxItem comoBoxItem = comboBox.SelectedValue as ComboBoxItem;
                Group newGroup = comoBoxItem.Tag as Group;
                services.MovePersonToGroup(person, curGroup, newGroup);
            }
            else if (mode == ModifyGroupMode.Add)
            {
                ComboBoxItem comoBoxItem = comboBox.SelectedValue as ComboBoxItem;
                Group newGroup = comoBoxItem.Tag as Group;
                services.AddPersonToGroup(person, newGroup);
            }

            this.Close();
        }

        private void Cancel_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.Close();
        }
    }
}
