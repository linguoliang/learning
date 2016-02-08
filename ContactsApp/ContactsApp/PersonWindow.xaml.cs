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
using Infrastructure;
using Service;

namespace ContactsApp
{
    /// <summary>
    /// PersonWindow.xaml 的交互逻辑
    /// </summary>
    public partial class PersonWindow : Window
    {
        Services services;
        Person person;
        EditMode mode;
        public PersonWindow(ref Services services, ref Person person, EditMode mode)
        {
            InitializeComponent();
            this.services = services;
            this.person = person;
            this.mode = mode;

            InitializeUI();
        }

        public void InitializeUI()
        {
            // load data
            Type t = typeof(Person);

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

                object value = property.GetValue(person);

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
                else if (property.PropertyType.IsGenericType)
                {
                    var valueList = value as List<Pair<Guid, Pair<string, string>>>;

                    if (valueList.Count != 0)
                    {
                        foreach (var v in valueList)
                        {
                            row++;
                            grid.RowDefinitions.Add(new RowDefinition());

                            TextBox subTextBoxName = new TextBox();
                            subTextBoxName.Name = "Name";
                            subTextBoxName.Text = v.Value.Value;
                            subTextBoxName.Uid = v.Key.ToString();
                            subTextBoxName.Tag = property;
                            subTextBoxName.SetValue(Grid.RowProperty, row);
                            subTextBoxName.SetValue(Grid.ColumnProperty, 1);
                            grid.Children.Add(subTextBoxName);

                            TextBox subTextBoxValue = new TextBox();
                            subTextBoxValue.Name = "Value";
                            subTextBoxValue.Text = v.Value.Key;
                            subTextBoxValue.Uid = v.Key.ToString();
                            subTextBoxValue.Tag = property;
                            subTextBoxValue.SetValue(Grid.RowProperty, row);
                            subTextBoxValue.SetValue(Grid.ColumnProperty, 2);
                            grid.Children.Add(subTextBoxValue);
                        }
                    }
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

        public void GeatherData(ref Person person)
        {
            foreach (var item in grid.Children)
            {
                if (item is TextBox)
                {
                    TextBox textBox = item as TextBox;
                    object tag = textBox.Tag;
                    PropertyInfo tagProperty = tag as PropertyInfo;

                    Type t = typeof(Person);
                    var properties = t.GetProperties();

                    foreach (PropertyInfo property in properties)
                    {
                        if (tagProperty != null && tagProperty.Name == property.Name)
                        {
                            if (property.PropertyType.ToString() == "System.String")
                            {
                                property.SetValue(person, textBox.Text);
                            }
                            else
                            {
                                if (!property.PropertyType.IsGenericType)
                                {
                                    var instance = Activator.CreateInstance(property.PropertyType, textBox.Text);
                                    property.SetValue(person, instance);
                                }
                                else
                                {
                                    // is id exist
                                    if (!person.isGUIDExist(textBox.Uid))
                                    {
                                        // if not, create and add to person
                                        var value = new Pair<Guid, Pair<string, string>> { Key = Guid.NewGuid() };

                                        var oldList = property.GetValue(person) as List<Pair<Guid, Pair<string, string>>>;
                                        oldList.Add(value);
                                    }
                                    else
                                    {
                                        // if yes, update
                                        if (textBox.Name == "Name")
                                        {
                                            var oldList = property.GetValue(person) as List<Pair<Guid, Pair<string, string>>>;

                                            var value = oldList.Find(v => v.Key.ToString() == textBox.Uid);
                                            value.Value.Value = textBox.Text;
                                        }
                                        else if (textBox.Name == "Value")
                                        {
                                            var oldList = property.GetValue(person) as List<Pair<Guid, Pair<string, string>>>;

                                            var value = oldList.Find(v => v.Key.ToString() == textBox.Uid);
                                            value.Value.Key = textBox.Text;
                                        }
                                    }
                                }
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
                        GeatherData(ref person);
                        services.AddPerson(person);
                        this.Close();
                    }
                    break;
                case EditMode.Update:
                    {
                        GeatherData(ref person);
                        services.UpdatePerson(person);
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
