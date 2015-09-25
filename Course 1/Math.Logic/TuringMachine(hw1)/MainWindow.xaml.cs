using System.Windows.Controls.Primitives;
using System.Windows.Media.Animation;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Data;  
using System.Windows;
using System.Linq;
using System.IO;
using System;

namespace Space {
    public partial class MainWindow : Window {
        private ManageCenter Controller = new ManageCenter();
        private Thickness Offset; // Specially for animations
        private string MashineState { 
            get{ return StateIndicator.Text; } 
            set{ StateIndicator.Text = value; }
        }
        #region Some Consts
        private const double AnimationSpeed = 0.3;
        private const int TapeBlockMargin = 2;
        private const int TapeBlockWidth = 20;
        private const int BorderWidth = 2;
        private const int LeftBarrier = 14;
        private int RightBarrier; // Damn, it's really not a const :)
        #endregion
        
        public MainWindow() {
            InitializeComponent();
            Controller.ReadComponents();
            
            this.FillTape();
            this.FillInterpreter();
            this.FillPointerLexicon();
            
            Controller.Clock.Interval = new TimeSpan(0, 0, 0, 0, (int)(AnimationSpeed*1000));
            Controller.Clock.Tick += ExecuteCurrentCommand;
            VisualLog.ItemsSource = Controller.LogList;
            MashineState = Controller.States[0];
            Offset = Tape.Margin;
        }
        private void FillTape() {
            RightBarrier = LeftBarrier + Controller.Tape.Count-1;

            for (int i = 0; i < 50; i++) {
                TextBox CurrentBlock = new TextBox();
                CurrentBlock.IsEnabled = false;
                if (i < LeftBarrier || i > RightBarrier) {
                    CurrentBlock.Text = "S0";
                    CurrentBlock.BorderBrush = Brushes.Red;
                } else { 
                    CurrentBlock.Text = Controller.Tape[i - LeftBarrier];
                    CurrentBlock.BorderBrush = Brushes.Black;
                }
                CurrentBlock.BorderThickness = new Thickness(BorderWidth);
                CurrentBlock.Margin = new Thickness(TapeBlockMargin);
                CurrentBlock.Width = TapeBlockWidth;
                Tape.Children.Add(CurrentBlock);
            }
        } 
        private void FillInterpreter() {
            for (int i = 0; i < Controller.InterpreterGrid[0].Count(); i++) {
                var column = new DataGridTextColumn();
                column.Header = Controller.InterpreterGrid[0][i];
                column.Binding = new Binding(string.Format("[{0}]", i)); // Those Parse-string bindings :\
                Interpreter.Columns.Add(column);
            }
            Interpreter.ItemsSource = Controller.InterpreterGrid;
        } 
        private void FillPointerLexicon() {
            for(int i = 0; i < Controller.Lexicon.Count; i++) {
                TextBox CurrentCell = new TextBox();
                CurrentCell.BorderThickness = new Thickness(BorderWidth);
                CurrentCell.Margin = new Thickness(TapeBlockMargin);
                CurrentCell.IsEnabled = false;
                CurrentCell.Width = PointerMind.Width/Controller.Lexicon.Count - CurrentCell.BorderThickness.Left - CurrentCell.Margin.Left;
                CurrentCell.Text = Controller.Lexicon[i];
                if (i == PointerIndex) 
                    CurrentCell.BorderBrush = Brushes.Red;
                else
                    CurrentCell.BorderBrush = Brushes.Black;
                PointerMind.Children.Add(CurrentCell);
            }
        }

        private TextBox SelectedTapeChild {
            get { return (TextBox)Tape.Children[TapeIndex]; }
        }
        private int TapeIndex {
            // just math, don't be scary :)
            get { return LeftBarrier - (int)Offset.Left/(TapeBlockWidth + TapeBlockMargin + BorderWidth); }
        }
        private string PointerWord {
            get { 
                TextBox txtb = PointerMind.Children[PointerIndex] as TextBox;
                return txtb.Text;
            }
        }
        private int PointerIndex {
            get; set;
        }

        void ExecuteCurrentCommand(object sender, EventArgs e) {
            TextBlock cellInside = (TextBlock)GetSelectedCell().Content;
            TuringCommand command = new TuringCommand(cellInside.Text);

            Controller.LogList.Insert(0, GetTapeAsString());
            
            MashineState = command.State;
            SelectedTapeChild.Text = command.Value;

            switch(command.PointerCommand) {
                case PointerCommand.L: PullTapeLeft(this, null); break;
                case PointerCommand.R: PullTapeRight(this, null); break;
                case PointerCommand.C: break;

                default: throw new ArgumentException("Incorrect Pointer Command.");
            }
            if (MashineState == "q0") {
                MessageBox.Show("Mashine State is 'q0'.\nWriting to output and shutting down");
                Controller.LogList.Insert(0, GetTapeAsString()); // Don't forget to write last tape 
                using (StreamWriter writer = new StreamWriter("TuringResult.txt"))
                    foreach (var LogString in Controller.LogList)
                        writer.WriteLine(LogString);
                Environment.Exit(0);
            }
            ShowSelectedCell();
        }
        private string GetTapeAsString() {
            string result = "..._";
            for (int i = LeftBarrier; i < RightBarrier+1; i++) {
			    TextBox txtb =  (TextBox)Tape.Children[i];
                result += txtb.Text + "_";
			}
            return result + "...";
        }
        private void ShowSelectedCell() {
            // +1 coz datagrid shows also vartiants of states & values
            SelectCellByIndex(Interpreter, Controller.States.IndexOf(MashineState)+1, Controller.Lexicon.IndexOf(SelectedTapeChild.Text)+1); 
        }
        private DataGridCell GetSelectedCell() {
            // why +1 to row and column? Look up.
            DataGridRow row = Interpreter.ItemContainerGenerator.ContainerFromIndex(Controller.States.IndexOf(MashineState)+1) as DataGridRow;
            DataGridCell Cell = GetCell(Interpreter, row, Controller.Lexicon.IndexOf(SelectedTapeChild.Text)+1);
            
            return Cell;
        }
        private void SelectCellByIndex(DataGrid dataGrid, int rowIndex, int columnIndex) {
            if (!dataGrid.SelectionUnit.Equals(DataGridSelectionUnit.Cell))
                throw new ArgumentException("The SelectionUnit of the DataGrid must be set to Cell.");
  
            if (rowIndex < 0 || rowIndex > (dataGrid.Items.Count - 1))
                throw new ArgumentException(string.Format("{0} is an invalid row index.", rowIndex));

            if (columnIndex < 0 || columnIndex > (dataGrid.Columns.Count - 1))
                throw new ArgumentException(string.Format("{0} is an invalid column index.", columnIndex));
  
            dataGrid.SelectedCells.Clear();
  
            object item = dataGrid.Items[rowIndex]; //=Product X
            DataGridRow row = dataGrid.ItemContainerGenerator.ContainerFromIndex(rowIndex) as DataGridRow;
            if (row == null) {
                dataGrid.ScrollIntoView(item);
                row = dataGrid.ItemContainerGenerator.ContainerFromIndex(rowIndex) as DataGridRow;
            } else {
                DataGridCell cell = GetCell(dataGrid, row, columnIndex);
                if (cell != null) {
                    DataGridCellInfo dataGridCellInfo = new DataGridCellInfo(cell);
                    dataGrid.SelectedCells.Add(dataGridCellInfo);
                    cell.Focus();
                }
            }
        }
        private DataGridCell GetCell(DataGrid dataGrid, DataGridRow rowContainer, int column) {
            if (rowContainer != null) {
                DataGridCellsPresenter presenter = FindVisualChild<DataGridCellsPresenter>(rowContainer);
                if (presenter == null) {
                    rowContainer.ApplyTemplate();
                    presenter = FindVisualChild<DataGridCellsPresenter>(rowContainer);
                } else {
                    DataGridCell cell = presenter.ItemContainerGenerator.ContainerFromIndex(column) as DataGridCell;
                    if (cell == null) {
                        dataGrid.ScrollIntoView(rowContainer, dataGrid.Columns[column]);
                        cell = presenter.ItemContainerGenerator.ContainerFromIndex(column) as DataGridCell;
                    }
                    return cell;
                }
            }
            return null;
        }
        private static T FindVisualChild<T>(DependencyObject obj) where T : DependencyObject {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(obj); i++) {
                DependencyObject child = VisualTreeHelper.GetChild(obj, i);
                if (child != null && child is T)
                    return (T)child;
                else {
                    T childOfChild = FindVisualChild<T>(child);
                    if (childOfChild != null)
                        return childOfChild;
                }
            }
            return null;
        }

        private void KeyPressed(object sender, KeyEventArgs e) {
            switch(e.Key) {
                case Key.Q: PntrToLeftButt_Click(this, null); break;
                case Key.W: SetNextState(this, null); break;
                case Key.E: PntrToRightButt_Click(this, null); break;
                case Key.A: PullTapeLeft(this, null); break;
                case Key.S: SetLastState(this, null); break;
                case Key.D: PullTapeRight(this, null); break;
                case Key.Space: OverrideWord(this, null); break;
            }
        }
        private void DragWindow(object sender, MouseButtonEventArgs e) {
            DragMove();
        }
        private void SetNextState(object sender, RoutedEventArgs e) {
            int StateIndex = Controller.States.IndexOf(MashineState);
            if ( StateIndex  < Controller.States.IndexOf(Controller.States.Last()))
                MashineState = Controller.States[++StateIndex];;
            if (MashineState != "q0")
                ShowSelectedCell();
        }
        private void SetLastState(object sender, RoutedEventArgs e) {
            int StateIndex = Controller.States.IndexOf(MashineState);
            if ( StateIndex  > Controller.States.IndexOf(Controller.States.First()))    
                MashineState = Controller.States[--StateIndex];
            ShowSelectedCell();
        }
        private void PullTapeLeft(object sender, RoutedEventArgs e) {
            SelectedTapeChild.Background = Brushes.White;

            if (!Controller.IsMashineBusy && TapeIndex > LeftBarrier) {
                Controller.IsMashineBusy = true;
                Offset.Left += TapeBlockWidth + BorderWidth + TapeBlockMargin;
                var animation = new ThicknessAnimation(Offset, TimeSpan.FromSeconds(AnimationSpeed));
                animation.Completed += (object sender2, EventArgs e2) => {     
                    SelectedTapeChild.Background = Brushes.Red;
                    Controller.IsMashineBusy = false; 
                };
                Tape.BeginAnimation(MarginProperty, animation);
            } else {
                SelectedTapeChild.Background = Brushes.Red;
                MessageBox.Show("Tape Ended.");
            }

            if (MashineState != "q0")
                ShowSelectedCell();
        }
        private void PullTapeRight(object sender, RoutedEventArgs e) {
            SelectedTapeChild.Background = Brushes.White;

            if (!Controller.IsMashineBusy && TapeIndex < RightBarrier) {
                Controller.IsMashineBusy = true;
                Offset.Left -= TapeBlockWidth + BorderWidth + TapeBlockMargin;
                var animation = new ThicknessAnimation(Offset, TimeSpan.FromSeconds(AnimationSpeed));
                animation.Completed += (object sender2, EventArgs e2) => {
                    SelectedTapeChild.Background = Brushes.Red;
                    Controller.IsMashineBusy = false; 
                };
                Tape.BeginAnimation(MarginProperty, animation);
            } else {
                SelectedTapeChild.Background = Brushes.Red;
                MessageBox.Show("Tape Ended.");
            }

            if (MashineState != "q0")
                ShowSelectedCell();
        }
        private void PntrToRightButt_Click(object sender, RoutedEventArgs e) {
            if (PointerIndex < PointerMind.Children.Count-1) {
                TextBox Selected = (TextBox)PointerMind.Children[PointerIndex];
                Selected.BorderBrush = Brushes.Black;
                Selected = (TextBox)PointerMind.Children[++PointerIndex];
                Selected.BorderBrush = Brushes.Red;
            }
        }
        private void PntrToLeftButt_Click(object sender, RoutedEventArgs e) {
            if (PointerIndex > 0) {
                TextBox Selected = (TextBox)PointerMind.Children[PointerIndex];
                Selected.BorderBrush = Brushes.Black;
                Selected = (TextBox)PointerMind.Children[--PointerIndex];
                Selected.BorderBrush = Brushes.Red;
            }
        }
        private void OverrideWord(object sender, RoutedEventArgs e) {
            TextBox TXTBox = SelectedTapeChild; 
            TXTBox.Text = PointerWord;
        }
        private void TickButt_Click(object sender, RoutedEventArgs e) {
            //Can't bind click directly coz of timer EventHandler.
            ExecuteCurrentCommand(this, null);
        }
        private void StartButt_Click(object seder, RoutedEventArgs e) {
            if (!Controller.Clock.IsEnabled) {
                StartButt.Background = Brushes.Red;
                TickButt.Foreground = Brushes.Black;
                TickButt.IsEnabled = false;
                Controller.Clock.Start();
            } else {
                StartButt.Background = Brushes.DarkGoldenrod;
                TickButt.Foreground = Brushes.White;
                TickButt.IsEnabled = true;
                Controller.Clock.Stop();
            }
        }
        private void ExitButt_Click(object sender, RoutedEventArgs e) {
            App.Current.Shutdown();
        }
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         