#include <gtk/gtk.h>

void css_set(GtkCssProvider * provider, GtkWidget *g_widget);

int main(int argc, char *argv[])
{
    GtkWidget       *window;
    GtkWidget       *textview;
   
    GtkBuilder      *builder;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");
    
    textview = GTK_WIDGET(gtk_builder_get_object(builder, "text_space"));
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));  
    gtk_builder_connect_signals(builder, NULL);
       
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(provider, "glade/theme.css", NULL);
   
    css_set(provider, textview);
    
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

void css_set(GtkCssProvider * cssProvider, GtkWidget *g_widget)
{
    GtkStyleContext *context = gtk_widget_get_style_context(g_widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

