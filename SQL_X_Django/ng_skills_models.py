from django.db import models
from projects.models import Project, Category

class Skill(models.Model):
    name = models.CharField(max_length=100)
    course = models.CharField(max_length=100)
    mini_projects = models.ManyToManyField('projects.Project', blank=True)
    categories = models.ManyToManyField('projects.Category', blank=True)

    def __str__(self):
        return self.name
