#include <gtk/gtk.h>
#include <signal.h>

GtkBuilder      *builder; 

int main(int argc, char *argv[])
{
    GtkWidget       *window;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    //g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    // save file here <---
    gtk_main_quit();
}

// called when file chosen

void on_file_select_file_set(GtkFileChooser *chooser)
{
    gchar* str = gtk_file_chooser_get_uri(chooser);
    
    GtkStack * stack = GTK_STACK(gtk_builder_get_object(builder, "side_bar"));
    gtk_stack_set_visible_child_name(stack, "file_tree");
}
