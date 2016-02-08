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
using System.Reflection;
using Domain;
using Service;

namespace ContactsApp
{
    /// <summary>
    /// GroupWindow.xaml 的交互逻辑
    /// </summary>
    public partial class GroupWindow : Window
    {
        Services services;
        Group group;
        EditMode mode;
        public GroupWindow(ref Services services, ref Group group, EditMode mode)
        {
            InitializeComponent();
            this.services = services;
            this.group = group;
            this.mode = mode;

            InitializeUI();
        }

        public void InitializeUI()
        {
            // load data
            Type t = typeof(Group);

            var properties = t.GetProperties();

            int row = 0;
            foreach (PropertyInfo property in properties)
            {
                grid.RowDefinitions.Add(new RowDefinition());

                string propertyName = property.Name;

                Label label = new Label();
                label.Content = propertyName;
                label.SetValue(Grid.RowProperty, row);
                label.SetValue(Grid.ColumnProperty, 0);
                grid.Children.Add(label);

                TextBox textBox = new TextBox();
                textBox.Name = propertyName;
                textBox.SetValue(Grid.RowProperty, row);
                textBox.SetValue(Grid.ColumnProperty, 2);

                object value = property.GetValue(group);

                if (property.PropertyType.ToString() == "System.Guid")
                {
                    textBox.Text = value.ToString();
                    textBox.Tag = property;

                    grid.Children.Add(textBox);
                }
                else if (property.PropertyType.ToString() == "System.String")
                {
                    if (value != null)
                    {
                        textBox.Text = value.ToString();
                    }
                    textBox.Tag = property;

                    grid.Children.Add(textBox);
                }
                else if (property.PropertyType.ToString() == "System.Int32")
                {
                    textBox.Text = value.ToString();
                    textBox.Tag = property;

                    grid.Children.Add(textBox);
                }
                else if (property.PropertyType.IsGenericType)
                {

                }

                row++;
            }

            row++;
            grid.RowDefinitions.Add(new RowDefinition());

            Button buttonOK = new Button();
            buttonOK.Name = "buttonOK";
            buttonOK.Content = "OK";
            buttonOK.Width = 75;
            buttonOK.Height = 25;
            buttonOK.PreviewMouseLeftButtonDown += buttonOKPreviewMouseLeftButtonDown;
            buttonOK.SetValue(Grid.RowProperty, row);
            buttonOK.SetValue(Grid.ColumnProperty, 1);
            grid.Children.Add(buttonOK);

            Button buttonCancel = new Button();
            buttonCancel.Name = "buttonCancel";
            buttonCancel.Content = "Cancel";
            buttonCancel.Width = 75;
            buttonCancel.Height = 25;
            buttonCancel.PreviewMouseLeftButtonDown += buttonCancelPreviewMouseLeftButtonDown;
            buttonCancel.SetValue(Grid.RowProperty, row);
            buttonCancel.SetValue(Grid.ColumnProperty, 2);
            grid.Children.Add(buttonCancel);

            // setup ui component
            // textbox of amount is always not editable.
            foreach (var item in grid.Children)
            {
                if (item is TextBox && (item as TextBox).Name == "Amount")
                {
                    (item as TextBox).IsEnabled = false;
                }
            }

            switch (mode)
            {
                case EditMode.Info:
                    {
                        foreach (var item in grid.Children)
                        {
                            if (item is TextBox)
                            {
                                (item as TextBox).IsEnabled = false;
                            }
                            else if (item is Button)
                            {
                                Button button = item as Button;

                                if (button.Name == "buttonOK")
                                {
                                    button.IsEnabled = false;
                                }
                            }
                        }
                    }
                    break;
                case EditMode.New:
                    break;
                case EditMode.Update:
                    break;
                default:
                    break;
            }
        }

        public void GeatherData(ref Group group)
        {

            foreach (var item in grid.Children)
            {
                if (item is TextBox)
                {
                    TextBox textBox = item as TextBox;
                    object tag = textBox.Tag;
                    PropertyInfo tagProperty = tag as PropertyInfo;

                    Type t = typeof(Group);
                    var properties = t.GetProperties();

                    foreach (PropertyInfo property in properties)
                    {
                        if (tagProperty != null && tagProperty.Name == property.Name)
                        {
                            if (property.PropertyType.ToString() == "System.String")
                            {
                                property.SetValue(group, textBox.Text);
                            }
                            else if (property.PropertyType.ToString() == "System.Int32")
                            {
                                // dont't need to set amount
                            }
                            else
                            {
                                if (!property.PropertyType.IsGenericType)
                                {
                                    var instance = Activator.CreateInstance(property.PropertyType, textBox.Text);
                                    property.SetValue(group, instance);
                                }
                                // don't have to handle persons, user will maintain it.
                            }
                        }
                    }
                }
            }
        }

        public void buttonOKPreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            switch (mode)
            {
                case EditMode.Info:
                    // the button ok isn't enabled in Info mode.
                    break;
                case EditMode.New:
                    {
                        GeatherData(ref group);
                        services.AddGroup(group);
                        this.Close();
                    }
                    break;
                case EditMode.Update:
                    {
                        GeatherData(ref group);
                        services.UpdateGroup(group);
                        this.Close();
                    }
                    break;
                default:
                    break;
            }
        }

        public void buttonCancelPreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.Close();
        }
    }
}
