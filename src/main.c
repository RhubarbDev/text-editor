#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget       *window;
    GtkBuilder      *builder;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));  
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(window); 
   
    g_object_unref(builder);
            
    gtk_main();

    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    // save file here <---
    gtk_main_quit();
}

