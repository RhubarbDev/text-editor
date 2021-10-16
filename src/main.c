#include <gtk/gtk.h>
#include "save.h"
#include <stdio.h>

void css_set(GtkCssProvider * provider, GtkWidget *g_widget);

typedef enum { false, true } bool;

GtkWidget	*textview;
GtkWidget	*saveopen_button;
GtkWidget	*file_label;

int main(int argc, char *argv[])
{
    GtkWidget       *window; 
    GtkBuilder      *builder;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");
    
    textview = GTK_WIDGET(gtk_builder_get_object(builder, "text_space"));
    saveopen_button = GTK_WIDGET(gtk_builder_get_object(builder, "saveopen_button"));
    file_label = GTK_WIDGET(gtk_builder_get_object(builder, "file_label"));
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));  
    gtk_builder_connect_signals(builder, NULL);
    
    gtk_button_set_label(saveopen_button, "Open");
       
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

bool file = false; // if text file empty 

void on_textbuffer_changed()
{
    if (!file) { gtk_button_set_label(saveopen_button, "Save"); file = true; }
    // scan text and syntax highlight
}

void on_saveopen_button_clicked()
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
    char *text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    char path[9] = "test.txt\0"; // placeholder
    save_file(text, path);
    gtk_label_set_text(file_label, path);
}

void css_set(GtkCssProvider * cssProvider, GtkWidget *g_widget)
{
    GtkStyleContext *context = gtk_widget_get_style_context(g_widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

