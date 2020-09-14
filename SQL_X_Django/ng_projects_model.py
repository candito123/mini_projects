import os
from django.conf import settings
from django.db import models

class Project(models.Model):
    name = models.CharField(max_length=100)
    is_mini = models.BooleanField(default=False)
    motivation = models.TextField(blank=True)
    elaboration = models.TextField(blank=True)
    date = models.DateField(null=True)
    used_skills = models.ManyToManyField('skills.Skill', blank=True)
    categories = models.ManyToManyField('Category', blank=True)

    def __str__(self):
        return self.name

class Category(models.Model): # will be used for search
    name = models.CharField(max_length=100)

    def __str__(self):
        return self.name

class Photo(models.Model):
    photo = models.ImageField(upload_to='photos')

    project = models.ForeignKey(
        Project,
        on_delete=models.CASCADE,
        related_name='photos',
        blank=True, null=True,
    )

class Embedded(models.Model):
    name = models.CharField(max_length=100, blank=True)
    embedded = models.TextField() # use youtube link

    project = models.ForeignKey(Project, related_name='embeddeds', on_delete=models.CASCADE, blank=True, null=True)

    def __str__(self):
        return self.name

class Code(models.Model):
    code = models.TextField()

    project = models.ForeignKey(Project, related_name='codes', on_delete=models.CASCADE, blank=True, null=True)

    def __unicode__(self):
        return u"{}".format(self.project)

class File(models.Model): #pdf, doc, etc goes
    file = models.FileField(upload_to ='files')

    project = models.ForeignKey(Project, related_name='files', on_delete=models.CASCADE, blank=True, null=True)

    def __unicode__(self):
        return u"{}".format(self.project)

class Link(models.Model):
    name = models.CharField(max_length=100, blank=True)
    link = models.TextField()

    project = models.ForeignKey(Project, related_name='links', on_delete=models.CASCADE, blank=True, null=True)

    def __str__(self):
        return self.name
